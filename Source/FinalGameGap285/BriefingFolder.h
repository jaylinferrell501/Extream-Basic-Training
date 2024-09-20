// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractAbleObjectBase.h"
#include "BriefingFolder.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBriefFolderContent, UTexture2D*, Content);
UCLASS()
class FINALGAMEGAP285_API ABriefingFolder : public AInteractAbleObjectBase
{
	GENERATED_BODY()

	// Static Mesh Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Paper;

	// UImage for folder Contents
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UTexture2D* FolderContent;


public:
	// Sets default values for this actor's properties
	ABriefingFolder();

	// Declare a delegate instance
	FBriefFolderContent OnBriefFolderInteract;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(class AMainCharacter* MainCharacter) override;

};
