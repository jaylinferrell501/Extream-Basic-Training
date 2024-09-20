// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"

#include "Bullet762MM.h"
#include "MainCharacter.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AAssaultRifle::AAssaultRifle()
{
	// Box Collision
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
}

void AAssaultRifle::BeginPlay()
{
	Super::BeginPlay();
}

void AAssaultRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Check if the firing button is pressed and if one second has passed
	if (GetIsFiring() && GetAccumulatedTime() >= GetTimeBetweenShots())
	{

		if (GetCanFire())
		{
			MuzzleFlashComponent->Activate(true);
		}

		FireWeapon();

		// Reset the accumulated time after firing
		ResetAccumulatedTime();
	}
	else
	{
		MuzzleFlashComponent->Deactivate();
	}
}

void AAssaultRifle::OnInteract(AMainCharacter* MainCharacter)
{

	// log a message
	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Orange, TEXT("You have picked up the Assault Rifle!"));

	MainCharacter->SetArmed(true);

	MainCharacter->SetEquippedFirearm(this);

	SetFireArmOwner(MainCharacter);

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAssaultRifle::FireWeapon()
{
	// call the base class function
	Super::FireWeapon();

	if (!GetCanFire())
		return;

	
	// Use the weapon's location for spawning the bullet
	FVector SpawnLocation = GetBulletSpawnPoint()->GetComponentLocation();

	// Adjust the weapon's rotation to set X (pitch) to 89 degrees
	FRotator SpawnRotation = GetBulletSpawnPoint()->GetComponentRotation();

	// Spawn the bullet
	ABullet762MM* SpawnedBullet = GetWorld()->SpawnActor<ABullet762MM>(BulletBlueprint, SpawnLocation, SpawnRotation);

	if (!SpawnedBullet)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn bullet in AFirearmBase::FireWeapon"));
		return;
	}

	SpawnedBullet->SetFiredFrom(this);

	// Initialize the bullet's direction with the adjusted aim direction
	SpawnedBullet->InitializeBulletDirection(GetAimDirection());
}

int32 AAssaultRifle::ReloadWeapon()
{
	int32 Ammo = Super::ReloadWeapon();

	if (Ammo < 0)
	{
		return Ammo;
	}

	return Ammo;

	
}
