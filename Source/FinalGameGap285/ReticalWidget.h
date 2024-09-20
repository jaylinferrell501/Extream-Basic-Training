// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReticalWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API UReticalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ReticalNothingDetected;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ReticalInteractDetected;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ReticalEnemyDetected;


	void UpdateReticalState(AActor* Actor);
	void ResetReticalState();
};
