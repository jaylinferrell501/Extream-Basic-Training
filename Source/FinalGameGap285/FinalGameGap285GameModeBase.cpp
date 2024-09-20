// Copyright Epic Games, Inc. All Rights Reserved.


#include "FinalGameGap285GameModeBase.h"
#include "MainCharacterHUD.h"
#include "Kismet/GameplayStatics.h"

void AFinalGameGap285GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Log number of enemies

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainCharacterHUD* MainCharacterHUD = PC->GetHUD<AMainCharacterHUD>();

	if (MainCharacterHUD)
	{
		MainCharacterHUD->ShowRetical();

		MainCharacterHUD->ShowSupply();
		MainCharacterHUD->HideSupply();

		MainCharacterHUD->ShowDialogue();
		MainCharacterHUD->HideDialogue();
		MainCharacterHUD->BindAllDialogueTriggersInWorld();

		MainCharacterHUD->ShowBrief();
		MainCharacterHUD->HideBrief();
		MainCharacterHUD->BindAllFolderDelegatesInWorld();
	}


	PC->bShowMouseCursor = false;
	PC->SetInputMode(FInputModeGameOnly());
}
