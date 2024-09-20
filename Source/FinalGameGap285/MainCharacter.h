// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MainCharacter.generated.h"

class AEnemyCharacter;
class AMainCharacterHUD;

UCLASS()
class FINALGAMEGAP285_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	// ---------------------------- Camera Variables ----------------------------

	// Camera boom positioning the camera behind the character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Follow camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraZoomSpeed = 10.0f;  // Adjust this value to control the speed of zoom

	UPROPERTY()
	float OriginalCameraBoomLength;

	// CameraZoom
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float CameraZoom = 50.f;

	// ---------------------------- Camera Variables ----------------------------


	// ---------------------------- Input Variables ----------------------------

	// Mapping of input to movement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* MainCharacterMappingContext;

	// Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	// Sprint Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SprintAction;

	// Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	// Crouch Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	//Aim Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	// Attack Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	//Toggle Walk Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ToggleWalkAction;

	// Interact Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	// Interact Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ProgressDialogueAction;

	// ---------------------------- Input Variables ----------------------------


	// ---------------------------- Movement Variables ----------------------------

	// WalkSpeed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

	// RunSpeed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float RunSpeed;

	// RunSpeed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float SprintSpeed;

	// CrouchSpeed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchSpeed;

	//Base Melee Damage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float BaseMeleeDamage;

	// ---------------------------- Movement Variables ----------------------------


	// ---------------------------- Boolean MainCharacterState ----------------------------

	// bIsCrouching
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MainCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsCrouching;

	// bIsAiming
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MainCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming;

	// bIsAiming
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MainCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsArmed;

	bool bIsWalking;
	 
	bool bIsSprinting;

	// bIsAttacking
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MainCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	// bIsReloading
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MainCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsReloaded;

	// ---------------------------- Boolean MainCharacterState ----------------------------


	// ---------------------------- Retical ----------------------------

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Retical, meta = (AllowPrivateAccess = "true"))
	float MinTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Retical, meta = (AllowPrivateAccess = "true"))
	float MaxTraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Retical, meta = (AllowPrivateAccess = "true"))
	float TraceDistance;

	// Reference to the HUD
	class AMainCharacterHUD* MainCharacterHUD;

	float MaxInteractionDistance = 200;

	// ---------------------------- Retical ----------------------------

	// Currently looking at
	bool bIsSelected;

	// Equipped Firearm
	class AFirearmBase* EquippedFirearm;

	// Attack Sphere
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* AttackSphere;


public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Getter for Crouching
	bool GetCrouching() const { return bIsCrouching; }

	// Getter for Aiming
	bool GetAiming() const { return bIsAiming; }

	// Getter for Armed
	bool GetArmed() const { return bIsArmed; }

	// Setter for Armed
	void SetArmed(bool bArmed) { bIsArmed = bArmed; }

	// Getter for Walking
	bool GetWalking() const { return bIsWalking; }

	// Getter for EquippedFirearm
	AFirearmBase* GetEquippedFirearm() const { return EquippedFirearm; }

	// Getter for follow camera
	UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Setter for EquippedFirearm
	void SetEquippedFirearm(AFirearmBase* Firearm);

	// Attack Montage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* AttackMontage;

	// Reload Montage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* ReloadMontage;

	//Setter for reload
	void SetReloaded(bool bReloaded) { bIsReloaded = bReloaded; }

	//Getter for reload
	bool GetReloaded() const { return bIsReloaded; }

	// Set CanFireFromFirearm
	UFUNCTION(BlueprintCallable, Category = "Firearm")
	void SetCanFireFromFirearm(bool bCanFire);

	void ActivateAttackSphere(bool Activate);

	// Get MainCharacterHUD
	AMainCharacterHUD* GetMainCharacterHUD() const { return MainCharacterHUD; }
private:

	void CheckRetical();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called for move input
	void Move(const FInputActionValue& Value);

	// Called for look input
	void Look(const FInputActionValue& Value);

	// Called for sprint input
	void StartSprint(const FInputActionValue& Value);

	// Called for stop sprint input
	void StopSprint(const FInputActionValue& Value);

	// Called for Crouch input
	void Crouched(const FInputActionValue& Value);

	// Called for Aim input
	void Aim(const FInputActionValue& Value);

	// Called for stop Aim input
	void StopAim(const FInputActionValue& Value);

	// Called for Toggle Walk input
	void ToggleWalk(const FInputActionValue& Value);

	// Called for Interact input
	void Interact(const FInputActionValue& Value);

	// called for Fire Weapon input
	void Attack(const FInputActionValue& Value);

	// called for Stop Fire Weapon input
	void StopAttack(const FInputActionValue& Value);

	// called for Progress Dialogue input
	void ProgressDialogue(const FInputActionValue& Value);



	UFUNCTION()
	void OnAttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PlayReloadWeaponMontage();

};
