// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoorBase.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API ADoor : public ADoorBase
{
	GENERATED_BODY()

public:
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(class AMainCharacter* MainCharacter) override;
	
};
