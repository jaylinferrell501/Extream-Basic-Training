// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueTrigger.generated.h"

class UBoxComponent;
class UDialogue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueTrigger, TArray<FString>, DialogueLines);
UCLASS()
class FINALGAMEGAP285_API ADialogueTrigger : public AActor
{
	GENERATED_BODY()

	// Trigger Box
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	UBoxComponent* TriggerBox;

	// A array of Dialogue lines
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta =(AllowPrivateAccess = true))
	TArray<FString> DialogueLines;

	// Bind to EnemyManager Delegate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	bool bIsBoundToEnemyManagerDelegate = false;

	//Is Collisions Enabled
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	bool bIsCollisionEnabled = true;

	// broadcast the dialogue lines on level start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (AllowPrivateAccess = true))
	bool bBroadcastOnLevelStart = false;
public:	
	// Sets default values for this actor's properties
	ADialogueTrigger();

	// Declare a delegate instance
	FDialogueTrigger OnTriggerDialogue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// OnOverlapBegin
	UFUNCTION()
	void OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void TurnOnCollision();
};
