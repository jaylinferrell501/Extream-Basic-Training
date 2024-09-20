// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTrigger.h"

#include "EnemyManager.h"
#include "MainCharacter.h"
#include "MainCharacterHUD.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADialogueTrigger::ADialogueTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Trigger Box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	// Bind the OnOverlapBegin event
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADialogueTrigger::OnBeginOverlapTrigger);
}

// Called when the game starts or when spawned
void ADialogueTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (bBroadcastOnLevelStart)
	{
		// Broadcast the dialogue lines
		OnTriggerDialogue.Broadcast(DialogueLines);
		// Disable the trigger box
		bIsCollisionEnabled = false;
	}


	if (bIsBoundToEnemyManagerDelegate)
	{
		// Find the EnemyManager in the current level
		AEnemyManager* EnemyManager = Cast<AEnemyManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyManager::StaticClass()));
		if (EnemyManager)
		{
			// Bind to the EnemyManager's delegate
			EnemyManager->OnAllEnemiesDead.AddDynamic(this, &ADialogueTrigger::TurnOnCollision);
		}
		else
		{
			// Log an error if the EnemyManager was not found
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("EnemyManager not found!")));
		}
	}
	
}

// Called every frame
void ADialogueTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsCollisionEnabled)
	{
		// Enable the trigger box
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		// Disable the trigger box
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADialogueTrigger::OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{

	// Cast the OtherActor to your MainCharacter class
	AMainCharacter* MainCharacterActor = Cast<AMainCharacter>(OtherActor);

	// Check if the cast was successful
	if (MainCharacterActor)
	{
		// The OtherActor is the MainCharacter
		OnTriggerDialogue.Broadcast(DialogueLines);

		// Disable the trigger box
		bIsCollisionEnabled = false;

	}
}

void ADialogueTrigger::TurnOnCollision()
{
	// Enable the trigger box
	bIsCollisionEnabled = true;
}

