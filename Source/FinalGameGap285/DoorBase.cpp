// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorBase.h"

#include "MainCharacter.h"

ADoorBase::ADoorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);

	// Initialize your variables
	InterpSpeed = 2.0f;
}

void ADoorBase::OpenDoor()
{
	bIsOpen = true;

	// Adjust the target rotation based on the door's start rotation and the defined open angle
	TargetRotation = FRotator(StartRotation.Pitch, StartRotation.Yaw + OpenAngle, StartRotation.Roll);
}

void ADoorBase::CloseDoor()
{
	bIsOpen = false;

	// Set the target rotation to close the door
	TargetRotation = StartRotation;
}

void ADoorBase::BeginPlay()
{
	Super::BeginPlay();

	// Obtain the current rotation of the door in the scene
	StartRotation = Door->GetComponentRotation();

	// Set the TargetRotation to the door's initial rotation
	TargetRotation = StartRotation;

	// Ensure bIsOpen is false to start with
	bIsOpen = false;

	// Set CurrentRotation to match the starting rotation of the door
	CurrentRotation = StartRotation;
}

void ADoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Interpolate the door's rotation towards the target rotation
	if (!CurrentRotation.Equals(TargetRotation, 0.01f))
	{
		CurrentRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpSpeed);
		Door->SetWorldRotation(CurrentRotation);
	}
}

void ADoorBase::OnInteract(AMainCharacter* MainCharacter)
{
	//Super::OnInteract(MainCharacter);

	if (MainCharacter != nullptr)
	{
		float DistanceToDoor = FVector::Dist(MainCharacter->GetActorLocation(), this->GetActorLocation());

		// Define a max distance at which the door can be interacted with
		float MaxInteractDistance = 250.0f;

		// Check if the character is within the interaction distance
		if (DistanceToDoor <= MaxInteractDistance)
		{
			// Toggle the state of the door
			if (bIsOpen)
			{
				CloseDoor();
			}
			else
			{
				OpenDoor();
			}
		}
	}
}
