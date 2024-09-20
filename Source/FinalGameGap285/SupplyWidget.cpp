// Fill out your copyright notice in the Description page of Project Settings.


#include "SupplyWidget.h"

#include "Components/TextBlock.h"

void USupplyWidget::UpdateAmmoAndClipText(int32 CurrentAmmo, int32 CurrentClip) const
{
	// Update the text
	CurrentAmmoText->SetText(FText::FromString(FString::FromInt(CurrentAmmo)));
	CurrentClipText->SetText(FText::FromString(FString::FromInt(CurrentClip)));
}
