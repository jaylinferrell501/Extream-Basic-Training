// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "EnemyCharacter.h"
//#include "EnemyCharacter.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyManager::AddEnemy(AEnemyCharacter* Enemy)
{
	Enemies.AddUnique(Enemy);
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Log Number of Enemies
	//GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, FString::Printf(TEXT("Number of Enemies: %d"), Enemies.Num()));

	// Iterate over the Enemies array using an iterator
	for (auto It = Enemies.CreateIterator(); It; ++It)
	{
		AEnemyCharacter* Enemy = *It;
		if (Enemy && Enemy->GetIsDead())
		{
			// Remove the dead enemy
			It.RemoveCurrent();
		}
	}

	// Check if all enemies are dead
	if (Enemies.Num() == 0)
	{
		// Log a message to the screen
		//GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Green, TEXT("All enemies are dead!"));

		bAllEnemiesDead = true;

		OnAllEnemiesDead.Broadcast();
	}

}

