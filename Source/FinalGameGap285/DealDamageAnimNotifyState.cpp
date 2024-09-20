// Fill out your copyright notice in the Description page of Project Settings.


#include "DealDamageAnimNotifyState.h"

#include "MainCharacter.h"

void UDealDamageAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float TotalDuration)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("NotifyBegin"));

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(MeshComp->GetOwner());
	if (MainCharacter)
	{
		MainCharacter->ActivateAttackSphere(true);
	}
}

void UDealDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UDealDamageAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("NotifyEnd"));

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(MeshComp->GetOwner());
	if (MainCharacter)
	{
		MainCharacter->ActivateAttackSphere(false);
	}
}
