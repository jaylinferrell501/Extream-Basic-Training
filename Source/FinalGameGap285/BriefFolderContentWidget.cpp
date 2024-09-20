// Fill out your copyright notice in the Description page of Project Settings.


#include "BriefFolderContentWidget.h"

#include "BriefingFolder.h"
#include "EngineUtils.h"
#include "Components/Image.h"

void UBriefFolderContentWidget::SetFolderContentImage(UTexture2D* FolderContentImage)
{
	// Set the image
	FolderContent->SetBrushFromTexture(FolderContentImage);

    SetVisibility(ESlateVisibility::Visible);

    bIsFolderOpen = true;
}

void UBriefFolderContentWidget::BindToAllFolderDelegates()
{
    int32 Count = 0;
    for (TActorIterator<ABriefingFolder> It(GetWorld()); It; ++It)
    {
        ABriefingFolder* BriefingFolder = *It;
        if (BriefingFolder)
        {
            BriefingFolder->OnBriefFolderInteract.AddDynamic(this, &UBriefFolderContentWidget::SetFolderContentImage);
            Count++;
            UE_LOG(LogTemp, Warning, TEXT("Bound trigger %s"), *BriefingFolder->GetObjectName());
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Total triggers bound: %d"), Count);
}
