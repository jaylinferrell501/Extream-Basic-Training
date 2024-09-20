// Fill out your copyright notice in the Description page of Project Settings.


#include "BriefingFolder.h"

ABriefingFolder::ABriefingFolder()
{
	// Static Mesh Component
	Paper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paper"));
	Paper->SetupAttachment(GetRootComponent());
}

void ABriefingFolder::BeginPlay()
{
	Super::BeginPlay();
}

void ABriefingFolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABriefingFolder::OnInteract(AMainCharacter* MainCharacter)
{
	OnBriefFolderInteract.Broadcast(FolderContent);
	SetIsInteractAble(false);
}
