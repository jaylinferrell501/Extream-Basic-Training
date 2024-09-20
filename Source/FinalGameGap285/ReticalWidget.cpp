// Fill out your copyright notice in the Description page of Project Settings.


#include "ReticalWidget.h"

#include "EnemyCharacter.h"
#include "InteractAbleObjectBase.h"
#include "Components/Image.h"

void UReticalWidget::UpdateReticalState(AActor* Actor)
{
    if (Actor != nullptr)
    {
        // Reset visibility of all reticle states
        ReticalNothingDetected->SetVisibility(ESlateVisibility::Hidden);
        ReticalEnemyDetected->SetVisibility(ESlateVisibility::Hidden);
        ReticalInteractDetected->SetVisibility(ESlateVisibility::Hidden);

        // Try casting to InteractableObjectBase actor class
        AInteractAbleObjectBase* InteractAbleObject = Cast<AInteractAbleObjectBase>(Actor);
        if (InteractAbleObject)
        {
            ReticalInteractDetected->SetVisibility(ESlateVisibility::Visible);
        }
        // Try casting to EnemyCharacter (or your specific enemy class)
        AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Actor);
        if (EnemyCharacter)
        {
            ReticalEnemyDetected->SetVisibility(ESlateVisibility::Visible);
        }

        // If Actor is neither interactable nor enemy
        if (!InteractAbleObject && !EnemyCharacter)
        {
            ReticalNothingDetected->SetVisibility(ESlateVisibility::Visible);
        }
    }
    else
    {
    	ResetReticalState();
	}
}

void UReticalWidget::ResetReticalState()
{
    ReticalNothingDetected->SetVisibility(ESlateVisibility::Visible);
    ReticalEnemyDetected->SetVisibility(ESlateVisibility::Hidden);
    ReticalInteractDetected->SetVisibility(ESlateVisibility::Hidden);
}
