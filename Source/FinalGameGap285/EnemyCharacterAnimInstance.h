// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API UEnemyCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "AnimationProperties")
	void UpdateAnimationProperties(float DeltaTime);

	// bIsIdle
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsIdle;

	// bIsAiming
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsAiming;

	// bIsDead
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsDead;

	// bIsInAgony
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAgony;


	//bIsGettingHit
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsGettingHit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class AEnemyCharacter* OwningPawn;
	
};
