// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "DialogueTrigger.h"
#include "EngineUtils.h"
#include "Components/TextBlock.h"

void UDialogueWidget::CreateDialogueSequence(TArray<FString> DialogueLines)
{
    SetVisibility(ESlateVisibility::Visible);

    bIsDialoguePlaying = true;

    DialogueSequence = DialogueLines;
    DialogueIndex = 0;  // Reset the dialogue index

    PlayNextDialogue(); // Start by displaying the first dialogue
}

void UDialogueWidget::PlayNextDialogue()
{
    // Clear the current text in the dialogue box
    DialogueText->SetText(FText::GetEmpty());

    if (DialogueIndex < DialogueSequence.Num())
    {
        CurrentDialogue = DialogueSequence[DialogueIndex];
        CurrentCharIndex = 0;  // Reset character index

        // Start the timer to display the next dialogue character by character
        GetWorld()->GetTimerManager().SetTimer(CharacterDisplayTimer, this, &UDialogueWidget::DisplayNextCharacter, CharacterDisplayInterval, true);
    }
    else
    {
        SetVisibility(ESlateVisibility::Hidden);
        bIsDialoguePlaying = false;
    }
}

void UDialogueWidget::PlayDialogueSequence()
{
    PlayNextDialogue(); // Start the sequence by playing the first dialogue
}

void UDialogueWidget::DisplayNextCharacter()
{
    if (CurrentCharIndex < CurrentDialogue.Len())
    {
        FString CharToDisplay = CurrentDialogue.Mid(CurrentCharIndex, 1);
        FString CurrentDisplayedText = DialogueText->GetText().ToString();
        CurrentDisplayedText.Append(CharToDisplay);
        DialogueText->SetText(FText::FromString(CurrentDisplayedText));
        CurrentCharIndex++;
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(CharacterDisplayTimer);
        DialogueIndex++;  // Move to the next dialogue, if necessary
    }
}

void UDialogueWidget::BindAllDialogueTriggersInWorld()
{
    int32 Count = 0;
    for (TActorIterator<ADialogueTrigger> It(GetWorld()); It; ++It)
    {
        ADialogueTrigger* TriggerVolume = *It;
        if (TriggerVolume)
        {
            TriggerVolume->OnTriggerDialogue.AddDynamic(this, &UDialogueWidget::CreateDialogueSequence);
            Count++;
            UE_LOG(LogTemp, Warning, TEXT("Bound trigger %s"), *TriggerVolume->GetName());
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Total triggers bound: %d"), Count);
}
