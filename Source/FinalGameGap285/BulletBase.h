// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

class USoundCue;
class AFirearmBase;
class UCapsuleComponent;

UCLASS()
class FINALGAMEGAP285_API ABulletBase : public AActor
{
	GENERATED_BODY()

	// Bullet Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BulletMesh;

	// Bullets Capsule Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* BulletCollision;

	// Bullet Impact sound Effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundCue* BulletImpactSound;

	// Bullet Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BulletSettings", meta = (AllowPrivateAccess = "true"))
	float BulletSpeed;

	// Bullet Damage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BulletSettings", meta = (AllowPrivateAccess = "true"))
	float BulletDamage;

	// Bullet Life Span
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BulletSettings", meta = (AllowPrivateAccess = "true"))
	float BulletLifeSpan;

	// Weapon that fired the bullet
	AFirearmBase* FiredFrom;


	// Bullet Direction
	FVector BulletDirection;

	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

	// Deal Damage
	void DealDamage(class AActor* OtherActor);

	// Set Owner
	void SetFiredFrom(AFirearmBase* NewOwner) { FiredFrom = NewOwner; }

	// Set initial direction of the bullet
	void InitializeBulletDirection(const FVector& Direction);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Bullet Collision
	UFUNCTION()
	virtual void OnBulletBeginOverlap_Trigger(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

};
