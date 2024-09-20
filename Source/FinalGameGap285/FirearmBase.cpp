// Fill out your copyright notice in the Description page of Project Settings.


#include "FirearmBase.h"

#include "MainCharacter.h"
#include "MainCharacterHUD.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Kismet/GameplayStatics.h"

AFirearmBase::AFirearmBase()
{
	ClipSize = 0;
	CurrentAmmo = 0;
	MaxAmmo = 0;
	bCanFire = true;
	bIsFiring = false;
	TimeBetweenShots = 1.f;

	BulletSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletSpawnPoint"));
	BulletSpawnPoint->SetupAttachment(RootComponent);

	// Initialize the muzzle flash component
	MuzzleFlashComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlashComponent"));
	MuzzleFlashComponent->SetupAttachment(BulletSpawnPoint); // Attach it to the weapon's root component or another appropriate component
	MuzzleFlashComponent->SetAutoActivate(false); // Prevent it from playing automatically
	
}

void AFirearmBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFirearmBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update the accumulated time
	AccumulatedTime += DeltaTime;

	if (Owner)
	{
		// Update the supply widget
		Owner->GetMainCharacterHUD()->UpdateSupply(CurrentAmmo, ClipSize);
	}

	
}

void AFirearmBase::FireWeapon()
{
	if (CurrentAmmo == 0 || !bCanFire)
	{
		// Play shooting sound if available
		if (OutOfAmmoSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OutOfAmmoSound, GetActorLocation());
		}

		return;
	}

	bCanFire = true;
	
	// Play shooting sound if available
	if (ShootingSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShootingSound, GetActorLocation());
	}


	CurrentAmmo--;

	if (CurrentAmmo <= 0)
	{
		CurrentAmmo = ReloadWeapon();
	}

}

int32 AFirearmBase::ReloadWeapon()
{
	bCanFire = false;

	if (ClipSize == 0)
	{
		return CurrentAmmo; // No ammo left to reload
	}

	int AmmoToLoad = FMath::Min(ClipSize, MaxAmmo);
	ClipSize -= AmmoToLoad;
	CurrentAmmo += AmmoToLoad;

	Owner->PlayReloadWeaponMontage();

	return CurrentAmmo;
}


