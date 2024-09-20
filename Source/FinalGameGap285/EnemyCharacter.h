// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class AFinalGameGap285GameModeBase;

UCLASS()
class FINALGAMEGAP285_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	// bIsIdle
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsIdle;

	// bIsAiming
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming;

	// bIsDead
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsDead;

	//bIsGettingHit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsGettingHit;

	// bIsInAgony
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacterState, meta = (AllowPrivateAccess = "true"))
	bool bIsInAgony;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacterState, meta = (AllowPrivateAccess = "true"))
	float Health;

	// Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyCharacterState, meta = (AllowPrivateAccess = "true"))
	FString Name;

	AFinalGameGap285GameModeBase* GameMode;


public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Get bIsIdle
	bool GetIsIdle() const { return bIsIdle; }

	// Get bIsAiming
	bool GetIsAiming() const { return bIsAiming; }

	// Get bIsDead
	bool GetIsDead() const { return bIsDead; }

	// Get IsInAgony
	bool GetIsInAgony() const { return bIsInAgony; }

	// Get bIsGettingHit
	bool GetIsGettingHit() const { return bIsGettingHit; }

	// GET name
	FString GetEnemyName() const { return Name; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
