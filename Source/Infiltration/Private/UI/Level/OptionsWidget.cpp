// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Level/OptionsWidget.h"
#include "Components/Button.h"
#include "Components/InputKeySelector.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

UOptionsWidget::UOptionsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InputSettings = UInputSettings::GetInputSettings();
	
	InteractionKeySelector->SetSelectedKey(GetActionMapping(MappingName[0]).Key);
	ForwardKeySelector->SetSelectedKey(GetAxisMapping(MappingName[1], true).Key);
	BackwardKeySelector->SetSelectedKey(GetAxisMapping(MappingName[1], false).Key);
	RightKeySelector->SetSelectedKey(GetAxisMapping(MappingName[2], true).Key);
	LeftKeySelector->SetSelectedKey(GetAxisMapping(MappingName[2], false).Key);

	InteractionKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnInteractKeySelected);
	ForwardKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnForwardKeySelected);
	BackwardKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnBackwardKeySelected);
	RightKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnRightKeySelected);
	LeftKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnLeftKeySelected);

	ReturnBtn->OnClicked.AddDynamic(this, &UOptionsWidget::Return);

	DisableErrorCanvas();
	ErrorKeyBtn->OnClicked.AddDynamic(this, &UOptionsWidget::DisableErrorCanvas);
}

void UOptionsWidget::Return()
{
	InputSettings->SaveKeyMappings();
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->BackToPauseMenu();
}

#pragma region KeyRebindButton
void UOptionsWidget::OnInteractKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[0]);
	}
	else
	{
		InputSettings->RemoveActionMapping(GetActionMapping(MappingName[0]));
		InputSettings->AddActionMapping(FInputActionKeyMapping(static_cast<FName>(MappingName[0]), InputChord.Key));	
	}
}

void UOptionsWidget::OnForwardKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[1], true);
	}
	else
	{
		InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[1], true));
		InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[1]), InputChord.Key, PositiveScale));	
	}
}

void UOptionsWidget::OnBackwardKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[1], false);
	}
	else
	{
		InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[1], false));
		InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[1]), InputChord.Key, NegativeScale));	
	}
}

void UOptionsWidget::OnRightKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[2], true);
	}
	else
	{
		InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[2], true));
		InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[2]), InputChord.Key, PositiveScale));	
	}
}

void UOptionsWidget::OnLeftKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[2], false);
	}
	else
	{
		InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[2], false));
		InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[2]), InputChord.Key, NegativeScale));	
	}
}
#pragma endregion 

#pragma region GetAction/AxisMapping
FInputActionKeyMapping UOptionsWidget::GetActionMapping(FString KeyName) const
{
	TArray<FInputActionKeyMapping> OutMappings;
	InputSettings->GetActionMappingByName(static_cast<FName>(KeyName), OutMappings);

	//check(OutMappings.Num() < 1);
	return OutMappings[0];
}

FInputAxisKeyMapping UOptionsWidget::GetAxisMapping(FString KeyName, const bool bPositiveScale) const
{
	TArray<FInputAxisKeyMapping> OutMappings;
	InputSettings->GetAxisMappingByName(static_cast<FName>(KeyName), OutMappings);

	FInputAxisKeyMapping KeyMapping;
	
	for (const auto Mapping : OutMappings)
	{
		if (bPositiveScale)
		{
			if (Mapping.Scale > 0)
			{
				KeyMapping = Mapping;
			}
		}
		else
		{
			KeyMapping = Mapping;
		}
	}

	return KeyMapping;
}
#pragma endregion

#pragma region ErrorKey
bool UOptionsWidget::IsAvailableKey(const FKey Key)
{
	InputSettings = UInputSettings::GetInputSettings();

	for (auto ActionKeyMapping : InputSettings->GetActionMappings())
	{
		if (ActionKeyMapping.Key == Key) return true;	
	}

	for (auto AxisKeyMapping : InputSettings->GetAxisMappings())
	{
		if (AxisKeyMapping.Key == Key) return true;
	}

	return false;
}

void UOptionsWidget::ErrorKey(const FString NameMapping, const bool bPositiveScale) const
{
	CanvasPanelErrorKey->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (NameMapping == MappingName[0])
	{
		InteractionKeySelector->SetSelectedKey(GetActionMapping(NameMapping).Key);
	}
	else if (NameMapping == MappingName[1])
	{
		if (bPositiveScale)
			ForwardKeySelector->SetSelectedKey(GetAxisMapping(NameMapping, bPositiveScale).Key);
		else
			BackwardKeySelector->SetSelectedKey(GetAxisMapping(NameMapping, bPositiveScale).Key);
	}
	else if (NameMapping == MappingName[2])
	{
		if (bPositiveScale)
			RightKeySelector->SetSelectedKey(GetAxisMapping(NameMapping, bPositiveScale).Key);
		else
			LeftKeySelector->SetSelectedKey(GetAxisMapping(NameMapping, bPositiveScale).Key);
	}
}
#pragma endregion