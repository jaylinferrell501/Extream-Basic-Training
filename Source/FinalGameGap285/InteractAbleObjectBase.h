// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractAbleObjectBase.generated.h"

UCLASS()
class FINALGAMEGAP285_API AInteractAbleObjectBase : public AActor
{
	GENERATED_BODY()

	// Static Mesh Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	// Bool for if the object is interactable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObjectSettings", meta = (AllowPrivateAccess = "true"))
	bool bIsInteractAble;

	// Name of the object
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ObjectSettings", meta = (AllowPrivateAccess = "true"))
	FString ObjectName;

	// A description of the object
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ObjectSettings", meta = (AllowPrivateAccess = "true"))
	FString ObjectDescription;
	
public:
	// Sets default values for this actor's properties
	AInteractAbleObjectBase();

	// Getter for IsInteractAble
	bool GetIsInteractAble() const { return bIsInteractAble; }

	// Setter for IsInteractAble
	void SetIsInteractAble(bool IsInteractAble) { bIsInteractAble = IsInteractAble; }

	// Getter for ObjectName
	FString GetObjectName() const { return ObjectName; }

	// Getter for ObjectDescription
	FString GetObjectDescription() const { return ObjectDescription; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(class AMainCharacter* MainCharacter) {};

};
