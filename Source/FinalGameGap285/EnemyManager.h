// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class AEnemyCharacter;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAllEnimiesDead);
UCLASS()
class FINALGAMEGAP285_API AEnemyManager : public AActor
{
	GENERATED_BODY()

	TArray<AEnemyCharacter*> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Eneimes, meta = (AllowPrivateAccess = "true"))
	bool bAllEnemiesDead = false;
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

	// Add an enemy to the list of enemies
	void AddEnemy(AEnemyCharacter* Enemy);

	FAllEnimiesDead OnAllEnemiesDead;

	bool AreAllEnemiesDead() const { return bAllEnemiesDead; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
