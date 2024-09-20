// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractAbleObjectBase.h"
#include "NiagaraSystem.h"
#include "FirearmBase.generated.h"

/**
 * 
 */

class ABulletBase;

UCLASS()
class FINALGAMEGAP285_API AFirearmBase : public AInteractAbleObjectBase
{
	GENERATED_BODY()

	// Bullet Spawn Point
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BulletSpawnPoint;

	// Gun Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundWave* ShootingSound;

	//out of ammo sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundWave* OutOfAmmoSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UNiagaraSystem* MuzzleFlashNiagara;

	// Clip Size
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FirearmSettings", meta = (AllowPrivateAccess = "true"))
	int32 ClipSize;

	// Current Ammo
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FirearmSettings", meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo;

	// Current Ammo
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FirearmSettings", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmo;

	// Weapon is firing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FirearmSettings", meta = (AllowPrivateAccess = "true"))
	bool bIsFiring;

	// Time per shot
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FirearmSettings", meta = (AllowPrivateAccess = "true"))
	float TimeBetweenShots;

	float AccumulatedTime;

	bool bCanFire;

	// Owner of the weapon
	AMainCharacter* Owner;

	// Weapon aim direction
	FVector AimDirection;

public:
	AFirearmBase();

	// Get Current Ammo
	int32 GetCurrentAmmo() const { return CurrentAmmo; }

	// Get Clip Size
	int32 GetClipSize() const { return ClipSize; }

	// Get is Firing
	bool GetIsFiring() const { return bIsFiring; }

	// Set is Firing
	void SetIsFiring(bool bNewIsFiring) { bIsFiring = bNewIsFiring; }

	// Get Can Fire
	bool GetCanFire() const { return bCanFire; }

	// Set Can Fire
	void SetCanFire(bool bNewCanFire) { bCanFire = bNewCanFire; }

	// get Accumulated Time
	float GetAccumulatedTime() const { return AccumulatedTime; }
	// reset Accumulated Time
	void ResetAccumulatedTime() { AccumulatedTime = 0.f; }

	// Set Weapon Aim Direction
	void SetAimDirection(const FVector& NewAimDirection) { AimDirection = NewAimDirection; }

	// Get Weapon Aim Direction
	FVector GetAimDirection() const { return AimDirection; }

	// Spawn BulletPoint
	UStaticMeshComponent* GetBulletSpawnPoint() const { return BulletSpawnPoint; }

	// Set Owner
	void SetFireArmOwner(AMainCharacter* NewOwner) { Owner = NewOwner; }

	// Get Owner
	AMainCharacter* GetFireArmOwner() const { return Owner; }


	// get Time Between Shots
	float GetTimeBetweenShots() const { return TimeBetweenShots; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	UNiagaraComponent* MuzzleFlashComponent;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void FireWeapon();

	virtual  int32 ReloadWeapon();
	
};
