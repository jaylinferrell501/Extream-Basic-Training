// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

#include "FirearmBase.h"
#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Bullet Mesh
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	SetRootComponent(BulletMesh);

	// Bullets Capsule Collision
	BulletCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BulletCollision"));
	BulletCollision->SetupAttachment(RootComponent);
	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ABulletBase::OnBulletBeginOverlap_Trigger);

	// Bullet Speed
	BulletSpeed = 1000.f;

	// Bullet Damage
	BulletDamage = 3.f;

	// Bullet Life Span
	BulletLifeSpan = 10.f;

}

void ABulletBase::DealDamage(AActor* OtherActor)
{
	// Cast to check if the other actor is a bullet, without losing the original reference
	ABulletBase* BulletActor = Cast<ABulletBase>(OtherActor);

	if (BulletActor)
	{
		// Logic if it hits another bullet, like destroying this bullet or something else
		Destroy();
		return;
	}

	// Play shooting sound if available, assuming it should happen when hitting non-bullet actors
	if (BulletImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BulletImpactSound, GetActorLocation());
	}

	// Apply damage if OtherActor is not a bullet
	if (OtherActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor, BulletDamage, FiredFrom->GetFireArmOwner()->GetController(), this, UDamageType::StaticClass());
	}

	// Destroy the bullet in all cases after this logic
	Destroy();
}

void ABulletBase::InitializeBulletDirection(const FVector& Direction)
{
	BulletDirection = Direction.GetSafeNormal();
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update bullet's lifespan
	BulletLifeSpan -= DeltaTime;
	if (BulletLifeSpan <= 0)
	{
		// Destroy the bullet or handle it as needed
		Destroy();
		return;
	}

	// Move the bullet
	FVector NewLocation = GetActorLocation() + (BulletDirection * BulletSpeed * DeltaTime);
	SetActorLocation(NewLocation);

}

void ABulletBase::OnBulletBeginOverlap_Trigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	DealDamage(OtherActor);
}

