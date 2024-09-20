// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"
#include "Bullet762MM.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API ABullet762MM : public ABulletBase
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ABullet762MM();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnBulletBeginOverlap_Trigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult) override;
	
};
