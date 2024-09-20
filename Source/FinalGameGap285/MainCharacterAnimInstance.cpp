// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"
#include "MainCharacter.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningPawn == nullptr)
	{
		OwningPawn = Cast<AMainCharacter>(TryGetPawnOwner());
	}
}

void UMainCharacterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (OwningPawn == nullptr)
	{
		OwningPawn = Cast<AMainCharacter>(TryGetPawnOwner());
	}

	if (OwningPawn)
	{
		FVector Speed = OwningPawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);

		MovementSpeed = LateralSpeed.Size();
		bIsInAir = OwningPawn->GetMovementComponent()->IsFalling();
		bIsCrouched = OwningPawn->GetCrouching();
		bIsAiming = OwningPawn->GetAiming();
		bIsArmed = OwningPawn->GetArmed();

		// Calculate Direction
		Direction = UKismetAnimationLibrary::CalculateDirection(Speed, OwningPawn->GetActorRotation());

		FRotator PawnRotation = OwningPawn->GetActorRotation();
		FRotator ControllerRotation = OwningPawn->GetControlRotation();
		FRotator DeltaRotation = ControllerRotation - PawnRotation;

		FRotator Interp = FMath::RInterpTo(FRotator(AimPitch, AimYaw, 0), DeltaRotation, DeltaTime, 20.f);
		AimPitch = FMath::ClampAngle(Interp.Pitch, -90.f, 90.f);

	}
}
