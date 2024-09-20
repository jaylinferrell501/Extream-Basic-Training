// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirearmBase.h"
#include "AssaultRifle.generated.h"

class UBoxComponent;
class ABullet762MM;
/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API AAssaultRifle : public AFirearmBase
{
	GENERATED_BODY()

	// Type of bullet
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABullet762MM> BulletBlueprint;

	// Box collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

public:
	AAssaultRifle();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(class AMainCharacter* MainCharacter) override;

	virtual void FireWeapon() override;

	virtual int32 ReloadWeapon() override;

};
