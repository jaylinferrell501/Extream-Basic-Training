// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacterAnimInstance.h"

#include "EnemyCharacter.h"

void UEnemyCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningPawn == nullptr)
	{
		OwningPawn = Cast<AEnemyCharacter>(TryGetPawnOwner());
	}
}


void UEnemyCharacterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (OwningPawn == nullptr)
	{
		OwningPawn = Cast<AEnemyCharacter>(TryGetPawnOwner());
	}

	if (OwningPawn)
	{
		bIsIdle = OwningPawn->GetIsIdle();
		bIsAiming = OwningPawn->GetIsAiming();
		bIsDead = OwningPawn->GetIsDead();
		bIsGettingHit = OwningPawn->GetIsGettingHit();
		bIsInAgony = OwningPawn->GetIsInAgony();
	}
}
