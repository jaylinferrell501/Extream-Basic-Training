// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractAbleObjectBase.h"
#include "DoorBase.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API ADoorBase : public AInteractAbleObjectBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = StaticMesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Door;

	// In your class definition
	UPROPERTY(EditAnywhere, Category = "DoorSettings", meta = (AllowPrivateAccess = true))
	float OpenAngle = 90.0f; // This is how far the door will open

	UPROPERTY(EditAnywhere, Category = "DoorSettings", meta = (AllowPrivateAccess = true))
	bool bIsOpen;

	UPROPERTY(EditAnywhere, Category = "DoorSettings", meta = (AllowPrivateAccess = true))
	FRotator CurrentRotation;

	UPROPERTY(EditAnywhere, Category = "DoorSettings", meta = (AllowPrivateAccess = true))
	FRotator TargetRotation;

	UPROPERTY(EditAnywhere, Category = "DoorSettings", meta = (AllowPrivateAccess = true))
	FRotator StartRotation;

	UPROPERTY(EditAnywhere, Category = "DoorSettings", meta = (AllowPrivateAccess = true))
	float InterpSpeed; // Speed at which the door opens
public:
	ADoorBase();

	void OpenDoor();

	void CloseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(class AMainCharacter* MainCharacter) override;


};
