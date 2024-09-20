// Fill out your copyright notice in the Description page of Project Settings.


#include "UserSaveGame.h"

#include "Kismet/GameplayStatics.h"

UUserSaveGame::UUserSaveGame()
{
	// Initialize default values here
	CurrentLevelName = TEXT("");
}

void UUserSaveGame::SaveData(FString LevelName)
{
	// Save the name of the current level
	CurrentLevelName = LevelName;

	// Save the data to disk
	UGameplayStatics::SaveGameToSlot(this, TEXT("UserSlot"), 0);
}

FString UUserSaveGame::LoadData()
{
    UUserSaveGame* LoadGameInstance = Cast<UUserSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("UserSlot"), 0));
    if (LoadGameInstance != nullptr)
    {
        // Set the name of the current level
        CurrentLevelName = LoadGameInstance->CurrentLevelName;

        return CurrentLevelName;
    }
    
	return TEXT("MainMenu");

}
