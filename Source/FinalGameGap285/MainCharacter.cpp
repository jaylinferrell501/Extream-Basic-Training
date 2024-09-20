// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "EnemyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FirearmBase.h"
#include "InteractAbleObjectBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacterHUD.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Don't rotate when the controller rotates. Let that just affect the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Setting Speeds
	WalkSpeed = 225.f;
	RunSpeed = 450.f;
	SprintSpeed = 900.f;
	CrouchSpeed = WalkSpeed;

	// Setting MainCharacterStates
	bIsWalking = false;
	bIsCrouching = false;
	bIsAiming = false;
	bIsArmed = false;

	// Trace Distance
	MinTraceDistance = 300.f;
	MaxTraceDistance = 10000;
	TraceDistance = MaxTraceDistance;

	// Attack SPHERE
	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	AttackSphere->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("LeftHandSocket"));
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnAttackSphereBeginOverlap);
	AttackSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Base Attack Damage
	BaseMeleeDamage = 10.f;

}


void AMainCharacter::SetEquippedFirearm(AFirearmBase* Firearm)
{
	// Attach the weapon to the desired socket
	if (Firearm->GetRootComponent())
	{
		Firearm->GetRootComponent()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GunHoldSocket"));

		EquippedFirearm = Firearm;

		MainCharacterHUD->ShowSupply();
	}
}


void AMainCharacter::SetCanFireFromFirearm(bool bCanFire)
{
	if (EquippedFirearm)
	{
		EquippedFirearm->SetCanFire(bCanFire);
	}
}

void AMainCharacter::ActivateAttackSphere(bool Activate)
{
	AttackSphere->SetCollisionEnabled(Activate ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
}

void AMainCharacter::CheckRetical()
{
	// Line Trace for Reticle Detection
	FHitResult HitResult;
	FVector StartLocation = FollowCamera->GetComponentLocation();
	FVector EndLocation = StartLocation + (FollowCamera->GetForwardVector() * TraceDistance);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore the player character

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

	// Resetting the reticle state and aim direction as a default action
	if (MainCharacterHUD)
	{
		MainCharacterHUD->ResetReticalState();
	}

	// Get the bullet spawn location from the equipped firearm
	FVector BulletSpawnLocation = EquippedFirearm ? EquippedFirearm->GetBulletSpawnPoint()->GetComponentLocation() : FVector::ZeroVector;

	// Process the hit result
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			FVector AimDirection = (HitResult.Location - BulletSpawnLocation).GetSafeNormal();

			// Handle interactable object
			AInteractAbleObjectBase* Interactable = Cast<AInteractAbleObjectBase>(HitActor);
			if (Interactable && Interactable->GetIsInteractAble())
			{
				float DistanceToActor = (HitActor->GetActorLocation() - GetActorLocation()).Size();

				if (DistanceToActor > MaxInteractionDistance)
				{
					// The hit actor is too far away to interact with
					bIsSelected = false;
					return;
				}

				MainCharacterHUD->UpdateReticalState(Interactable);

				if (bIsSelected && Interactable != nullptr)
				{
					Interactable->OnInteract(this);

					bIsSelected = false;
				}

				bIsSelected = false;
			}

			// Handle enemy character
			AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(HitActor);
			if (Enemy)
			{
				MainCharacterHUD->UpdateReticalState(Enemy);

				bIsSelected = false;
			}

			if (EquippedFirearm)
			{
				EquippedFirearm->SetAimDirection(AimDirection);
			}
		}
		else
		{
			MainCharacterHUD->UpdateReticalState(nullptr);

			bIsSelected = false;
		}
	}
	else
	{
		bIsSelected = false;
		if (EquippedFirearm)
		{
			EquippedFirearm->SetAimDirection(FollowCamera->GetForwardVector());
		}

		MainCharacterHUD->UpdateReticalState(nullptr);
	}
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

	OriginalCameraBoomLength = CameraBoom->TargetArmLength;

	// bind the input mapping context to the character
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MainCharacterMappingContext, 0);
		}
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	MainCharacterHUD = PC->GetHUD<AMainCharacterHUD>();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAiming)
	{
		// Movement towards camera forward vector
		GetCharacterMovement()->bOrientRotationToMovement = true;

		// Find out which way the camera is facing
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator CameraRotation(0, Rotation.Yaw, 0);

		// Smoothly interpolate the player's rotation towards the camera's rotation
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), CameraRotation, GetWorld()->GetDeltaSeconds(), 10);

		// Set the new rotation
		SetActorRotation(NewRotation);
	}


	// Smooth Zoom
	float TargetLength = bIsAiming ? (OriginalCameraBoomLength - CameraZoom) : OriginalCameraBoomLength;
	CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, TargetLength, DeltaTime, CameraZoomSpeed);

	CheckRetical();
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// bind the move action
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);

		// bind the look action
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		// bind the sprint action
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AMainCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMainCharacter::StopSprint);

		// bind the jump action
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMainCharacter::StopJumping);

		// bind the crouch action
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AMainCharacter::Crouched);

		// bind the aim action
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AMainCharacter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AMainCharacter::StopAim);

		// bind toggle walk action
		EnhancedInputComponent->BindAction(ToggleWalkAction, ETriggerEvent::Started, this, &AMainCharacter::ToggleWalk);

		// bind the interact action
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainCharacter::Interact);

		// bind the fire weapon action
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainCharacter::Attack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AMainCharacter::StopAttack);

		// bind the Progress Dialogue action
		EnhancedInputComponent->BindAction(ProgressDialogueAction, ETriggerEvent::Started, this, &AMainCharacter::ProgressDialogue);
	}
	
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	if (MainCharacterHUD->GetIsDialoguePlaying())
		return;

	if (MainCharacterHUD->GetIsBriefFolderOpen())
		return;

	if (bIsAiming && !bIsArmed)
	{
		return;
	}

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Camera rotation around Z only (yaw)
		const FRotator CameraRotationYaw(0, Controller->GetControlRotation().Yaw, 0);

		// Camera forward vector
		const FVector CameraForwardDirection = FRotationMatrix(CameraRotationYaw).GetUnitAxis(EAxis::X);

		// Get the dot product between the camera forward and the actor forward
		float DotProduct = FVector::DotProduct(GetActorForwardVector(), CameraForwardDirection);

		// if the camera and player are facing the same direction use strafe movement
		if (DotProduct > 0.99f)
		{
			// Strafe movement - player does not rotate to movement
			GetCharacterMovement()->bOrientRotationToMovement = false;

			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
		else
		{
			// Movement towards camera forward vector
			GetCharacterMovement()->bOrientRotationToMovement = true;

			// Find out which camera is facing
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator CameraRotation(0, Rotation.Yaw, 0);

			// Smoothly interpolate the player's rotation towards the camera's rotation
			FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), CameraRotation, GetWorld()->GetDeltaSeconds(), 15);

			// Set the new rotation
			SetActorRotation(NewRotation);

			// Get forward vector
			const FVector ForwardDirection = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::X);
			// Add movement in that direction
			AddMovementInput(ForwardDirection, MovementVector.Y);

			// Get right vector
			const FVector RightDirection = FRotationMatrix(NewRotation).GetUnitAxis(EAxis::Y);
			// Add movement in that direction
			AddMovementInput(RightDirection, MovementVector.X);
		}
	}

}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	if (MainCharacterHUD->GetIsBriefFolderOpen())
		return;

	// input is a Vector2D
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add movement
		AddControllerPitchInput(-LookVector.Y);
		AddControllerYawInput(LookVector.X);
	}
}

void AMainCharacter::StartSprint(const FInputActionValue& Value)
{
	if (MainCharacterHUD->GetIsBriefFolderOpen())
		return;

	if (bIsAiming)
		return;

	bIsSprinting = true;

	if (bIsCrouching)
		bIsCrouching = false;

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMainCharacter::StopSprint(const FInputActionValue& Value)
{
	if (bIsAiming)
		return;

	bIsSprinting = false;

	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMainCharacter::Crouched(const FInputActionValue& Value)
{
	if (MainCharacterHUD->GetIsBriefFolderOpen())
		return;

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

	if (bIsCrouching)
	{
		bIsCrouching = false;

		if (bIsAiming)
			return;

		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

		// Increase the capsule size and adjust its position when standing up
		CapsuleComp->SetCapsuleHalfHeight(CapsuleComp->GetScaledCapsuleHalfHeight() * 2);
	}
	else
	{
		bIsCrouching = true;
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;

		// Reduce the capsule size and adjust its position when crouching
		CapsuleComp->SetCapsuleHalfHeight(CapsuleComp->GetScaledCapsuleHalfHeight() / 2);
	}
}

void AMainCharacter::Aim(const FInputActionValue& Value)
{
	if (MainCharacterHUD->GetIsBriefFolderOpen())
		return;

	bIsAiming = true;
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (!bIsArmed)
	{
		MainCharacterHUD->HideRetical();
	}
}

void AMainCharacter::StopAim(const FInputActionValue& Value)
{
	bIsAiming = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

	MainCharacterHUD->ShowRetical();
}

void AMainCharacter::ToggleWalk(const FInputActionValue& Value)
{
	if (MainCharacterHUD->GetIsBriefFolderOpen())
		return;

	if (bIsWalking)
	{
		bIsWalking = false;
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
	else
	{
		bIsWalking = true;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AMainCharacter::Interact(const FInputActionValue& Value)
{
	if (MainCharacterHUD->GetIsDialoguePlaying())
		return;

	if (MainCharacterHUD->GetIsBriefFolderOpen())
		return;

	bIsSelected = true;
}

void AMainCharacter::Attack(const FInputActionValue& Value)
{

	if (MainCharacterHUD->GetIsDialoguePlaying())
		return;

	if (MainCharacterHUD->GetIsBriefFolderOpen())
		return;

	if (bIsSprinting)
		return;

	if (bIsArmed && EquippedFirearm)
	{
		EquippedFirearm->SetIsFiring(true);
	}

	if (!bIsArmed)
	{
		if (bIsAttacking)
			return;

		bIsAttacking = true;

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && AttackMontage)
		{
			AnimInstance->Montage_Play(AttackMontage);
		}
	}
}

void AMainCharacter::StopAttack(const FInputActionValue& Value)
{
	if (bIsSprinting)
		return;

	if (bIsArmed && EquippedFirearm)
	{
		EquippedFirearm->SetIsFiring(false);
	}
}

void AMainCharacter::ProgressDialogue(const FInputActionValue& Value)
{
	if (MainCharacterHUD->GetIsDialoguePlaying())
		MainCharacterHUD->ContinueDialogue();

	if (MainCharacterHUD->GetIsBriefFolderOpen())
		MainCharacterHUD->HideBrief();
}

void AMainCharacter::OnAttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor != this && OtherActor->IsA(ACharacter::StaticClass()))
	{
		//if (GEngine)
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("MainCharacter: Hit other character"));

		UGameplayStatics::ApplyDamage(OtherActor, BaseMeleeDamage, (Cast<ACharacter>(this)->GetController()), this, UDamageType::StaticClass());
	}
}

void AMainCharacter::PlayReloadWeaponMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ReloadMontage)
	{
		AnimInstance->Montage_Play(ReloadMontage);
	}
}

