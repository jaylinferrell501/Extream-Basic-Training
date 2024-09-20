// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class UDialogue;
/**
 * 
 */


UCLASS()
class FINALGAMEGAP285_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

	// Current Dialogue index
	size_t DialogueIndex = 0;

	// current Dialogue
	FString CurrentDialogue;

	// Dialogue Sequence
	TArray<FString> DialogueSequence;

	// Current Character Index
	size_t CurrentCharIndex = 0;

	// Timer Handle
	FTimerHandle CharacterDisplayTimer;

	// Character Display Interval
	float CharacterDisplayInterval = 0.05f;

	// Boolean to check if dialogue is playing
	bool bIsDialoguePlaying = false;

public:
	// Dialogue Box
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* DialogueBox;

	// Dialogue text
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DialogueText;

	// Bind Dialogue
	void BindAllDialogueTriggersInWorld();

	// Create Dialogue Sequence
	UFUNCTION()
	void CreateDialogueSequence(TArray<FString> DialogueLines);

	void PlayNextDialogue();

	// Get bIsDialoguePlaying
	bool GetIsDialoguePlaying() const { return bIsDialoguePlaying;  }


private:
	void PlayDialogueSequence();

	void DisplayNextCharacter();
};
