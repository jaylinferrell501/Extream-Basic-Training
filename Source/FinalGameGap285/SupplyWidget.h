// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SupplyWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API USupplyWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// Current ammo text
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentAmmoText;

	// Current Clip Text
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentClipText;

	// Update Ammo and Clip Text
	void UpdateAmmoAndClipText(int32 CurrentAmmo, int32 CurrentClip) const;
	
};
