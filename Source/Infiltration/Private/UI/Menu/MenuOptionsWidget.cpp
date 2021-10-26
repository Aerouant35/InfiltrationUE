// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/MenuOptionsWidget.h"
#include "Components/Button.h"
#include "Components/InputKeySelector.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Menu/MainMenuHUD.h"

UMenuOptionsWidget::UMenuOptionsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMenuOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InputSettings = UInputSettings::GetInputSettings();
	
	InteractionKeySelector->SetSelectedKey(GetActionMapping(MappingName[0]).Key);
	ForwardKeySelector->SetSelectedKey(GetAxisMapping(MappingName[1], true).Key);
	BackwardKeySelector->SetSelectedKey(GetAxisMapping(MappingName[1], false).Key);
	RightKeySelector->SetSelectedKey(GetAxisMapping(MappingName[2], true).Key);
	LeftKeySelector->SetSelectedKey(GetAxisMapping(MappingName[2], false).Key);

	InteractionKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnInteractKeySelected);
	ForwardKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnForwardKeySelected);
	BackwardKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnBackwardKeySelected);
	RightKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnRightKeySelected);
	LeftKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnLeftKeySelected);

	ReturnBtn->OnClicked.AddDynamic(this, &UMenuOptionsWidget::Return);

	DisableErrorCanvas();
	ErrorKeyBtn->OnClicked.AddDynamic(this, &UMenuOptionsWidget::DisableErrorCanvas);
}

void UMenuOptionsWidget::Return()
{
	InputSettings->SaveKeyMappings();
	Cast<AMainMenuHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->OptionsToMainMenu();
}

FInputActionKeyMapping UMenuOptionsWidget::GetActionMapping(FString KeyName) const
{
	TArray<FInputActionKeyMapping> OutMappings;
	InputSettings->GetActionMappingByName(static_cast<FName>(KeyName), OutMappings);

	//check(OutMappings.Num() < 1);
	return OutMappings[0];
}

FInputAxisKeyMapping UMenuOptionsWidget::GetAxisMapping(FString KeyName, const bool bPositiveScale) const
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

void UMenuOptionsWidget::OnInteractKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[0]);
		return;
	}
	
	InputSettings->RemoveActionMapping(GetActionMapping(MappingName[0]));
	InputSettings->AddActionMapping(FInputActionKeyMapping(static_cast<FName>(MappingName[0]), InputChord.Key));
}

void UMenuOptionsWidget::OnForwardKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[1], true);
		return;
	}

	InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[1], true));
	InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[1]), InputChord.Key, PositiveScale));
}

void UMenuOptionsWidget::OnBackwardKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[1], false);
		return;
	}

	InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[1], false));
	InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[1]), InputChord.Key, NegativeScale));
}

void UMenuOptionsWidget::OnRightKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[2], true);
		return;
	}

	InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[2], true));
	InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[2]), InputChord.Key, PositiveScale));
}

void UMenuOptionsWidget::OnLeftKeySelected(const FInputChord InputChord)
{
	if (IsAvailableKey(InputChord.Key))
	{
		ErrorKey(MappingName[2], false);
		return;
	}

	InputSettings->RemoveAxisMapping(GetAxisMapping(MappingName[2], false));
	InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[2]), InputChord.Key, NegativeScale));
}

bool UMenuOptionsWidget::IsAvailableKey(const FKey Key)
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

void UMenuOptionsWidget::ErrorKey(const FString NameMapping, const bool bPositiveScale) const
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