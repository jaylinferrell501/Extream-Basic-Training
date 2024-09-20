// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UserSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class FINALGAMEGAP285_API UUserSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UUserSaveGame();

	// Variable to store the name of the current level
	UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
	FString CurrentLevelName;

	// Function to save the data
	UFUNCTION(BlueprintCallable, Category = "SaveGameData")
	void SaveData(FString LevelName);

	// Function to load the data
	UFUNCTION(BlueprintCallable, Category = "SaveGameData")
	FString LoadData();
};
