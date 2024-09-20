// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractAbleObjectBase.h"

// Sets default values
AInteractAbleObjectBase::AInteractAbleObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh Component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	bIsInteractAble = false;
	ObjectName = "Default Object Name";
	ObjectDescription = "Default Object Description";
}

// Called when the game starts or when spawned
void AInteractAbleObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractAbleObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

