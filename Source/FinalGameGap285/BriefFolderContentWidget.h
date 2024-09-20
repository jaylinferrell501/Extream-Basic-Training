// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BriefFolderContentWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API UBriefFolderContentWidget : public UUserWidget
{
	GENERATED_BODY()

	bool bIsFolderOpen = false;
public:

	// Current Folder Image
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* FolderContent;

	// Set Folder Content Image
	UFUNCTION()
	void SetFolderContentImage(UTexture2D* FolderContentImage);

	//Bind the widget to all folder delegate
	void BindToAllFolderDelegates();

	//Get bIsFolderOpen
	bool GetIsFolderOpen() const { return bIsFolderOpen; }

	//Set bIsFolderOpen
	void SetIsFolderOpen(bool IsFolderOpen) { bIsFolderOpen = IsFolderOpen; }

};
