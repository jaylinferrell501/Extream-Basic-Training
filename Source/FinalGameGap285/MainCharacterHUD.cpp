// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"

#include "BriefFolderContentWidget.h"
#include "DialogueWidget.h"
#include "ReticalWidget.h"
#include "SupplyWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

void AMainCharacterHUD::ShowRetical()
{
	if (!ReticalWidget)
	{
		// Make widget owned by our player
		APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
		ReticalWidget = Cast<UReticalWidget>(CreateWidget(PlayerController, ReticalWidgetClass));

		ReticalWidget->AddToViewport();
	}
	else
	{
		ReticalWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainCharacterHUD::HideRetical()
{
	if (ReticalWidget)
	{
		ReticalWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainCharacterHUD::ShowDialogue()
{
	if (!DialogueWidget)
	{
		// Make widget owned by our player
		APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
		DialogueWidget = Cast<UDialogueWidget>(CreateWidget(PlayerController, DialogueWidgetClass));

		DialogueWidget->AddToViewport();
	}
	else
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainCharacterHUD::HideDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool AMainCharacterHUD::GetIsDialoguePlaying() const
{
	if (DialogueWidget)
	{
		return DialogueWidget->GetIsDialoguePlaying();
	}

	return false;
}

void AMainCharacterHUD::BindAllDialogueTriggersInWorld()
{
	if (DialogueWidget)
	{
		DialogueWidget->BindAllDialogueTriggersInWorld();
	}
}

void AMainCharacterHUD::BindAllFolderDelegatesInWorld()
{
	if (BriefFolderContentWidget)
	{
		BriefFolderContentWidget->BindToAllFolderDelegates();
	}
}

void AMainCharacterHUD::ContinueDialogue()
{
	if (DialogueWidget)
	{
		DialogueWidget->PlayNextDialogue();
	}
}

void AMainCharacterHUD::ShowSupply()
{
	if (!SupplyWidget)
	{
				// Make widget owned by our player
		APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
		SupplyWidget = Cast<USupplyWidget>(CreateWidget(PlayerController, SupplyWidgetClass));

		SupplyWidget->AddToViewport();
	}
	else
	{
		SupplyWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainCharacterHUD::HideSupply()
{
	if (SupplyWidget)
	{
		SupplyWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainCharacterHUD::UpdateSupply(int32 CurrentAmmo, int32 CurrentClip)
{
	if (SupplyWidget)
	{
		SupplyWidget->UpdateAmmoAndClipText(CurrentAmmo, CurrentClip);
	}
}

void AMainCharacterHUD::ShowBrief()
{
	if (!BriefFolderContentWidget)
	{
		// Make widget owned by our player
		APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
		BriefFolderContentWidget = Cast<UBriefFolderContentWidget>(CreateWidget(PlayerController, BriefFolderContentWidgetClass));

		BriefFolderContentWidget->AddToViewport();
	}
	else
	{
		BriefFolderContentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainCharacterHUD::HideBrief()
{
	if (BriefFolderContentWidget)
	{
		BriefFolderContentWidget->SetVisibility(ESlateVisibility::Hidden);
		BriefFolderContentWidget->SetIsFolderOpen(false);
	}
}

bool AMainCharacterHUD::GetIsBriefFolderOpen() const
{
	if (BriefFolderContentWidget)
	{
		return BriefFolderContentWidget->GetIsFolderOpen();
	}

	return false;
}

void AMainCharacterHUD::UpdateReticalState(AActor* Actor)
{
	if (ReticalWidget)
	{
		ReticalWidget->UpdateReticalState(Actor);
	}
}

void AMainCharacterHUD::ResetReticalState()
{
	if (ReticalWidget)
	{
		ReticalWidget->ResetReticalState();
	}
}
