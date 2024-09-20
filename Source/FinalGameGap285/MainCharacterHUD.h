// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainCharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API AMainCharacterHUD : public AHUD
{
	GENERATED_BODY()

public:
	// ----------------------------- Retical -----------------------------
	UFUNCTION(BlueprintCallable)
	void ShowRetical();
	UFUNCTION(BlueprintCallable)
	void HideRetical();

	UFUNCTION(BlueprintCallable)
	void UpdateReticalState(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void ResetReticalState();

	// ----------------------------- Retical -----------------------------

	// ----------------------------- Dialogue -----------------------------
	UFUNCTION(BlueprintCallable)
	void ShowDialogue();
	UFUNCTION(BlueprintCallable)
	void HideDialogue();

	UFUNCTION(BlueprintCallable)
	bool GetIsDialoguePlaying() const;

	UFUNCTION(BlueprintCallable)
	void BindAllDialogueTriggersInWorld();

	UFUNCTION(BlueprintCallable)
	void BindAllFolderDelegatesInWorld();

	UFUNCTION(BlueprintCallable)
	void ContinueDialogue();

	// ----------------------------- Dialogue -----------------------------

	// ----------------------------- Supply -----------------------------
	UFUNCTION(BlueprintCallable)
	void ShowSupply();

	UFUNCTION(BlueprintCallable)
	void HideSupply();

	UFUNCTION(BlueprintCallable)
	void UpdateSupply(int32 CurrentAmmo, int32 CurrentClip);

	// ----------------------------- Supply -----------------------------

	// ----------------------------- Brief -----------------------------

	UFUNCTION(BlueprintCallable)
	void ShowBrief();

	UFUNCTION(BlueprintCallable)
	void HideBrief();

	UFUNCTION(BlueprintCallable)
	bool GetIsBriefFolderOpen() const;

	// ----------------------------- Brief -----------------------------


protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> ReticalWidgetClass;

	UPROPERTY()
	class UReticalWidget* ReticalWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> DialogueWidgetClass;

	UPROPERTY()
	class UDialogueWidget* DialogueWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> SupplyWidgetClass;

	UPROPERTY()
	class USupplyWidget* SupplyWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> BriefFolderContentWidgetClass;

	UPROPERTY()
	class UBriefFolderContentWidget* BriefFolderContentWidget;
	
};
