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
	check(InputSettings != nullptr);
	
	InteractionKeySelector->SetSelectedKey(GetActionMapping(MappingName[0]).Key);
	ForwardKeySelector->SetSelectedKey(GetAxisMappingPositive(MappingName[1]).Key);
	BackwardKeySelector->SetSelectedKey(GetAxisMappingNegative(MappingName[1]).Key);
	RightKeySelector->SetSelectedKey(GetAxisMappingPositive(MappingName[2]).Key);
	LeftKeySelector->SetSelectedKey(GetAxisMappingNegative(MappingName[2]).Key);
	
	DisableErrorCanvas();
}

void UOptionsWidget::InitDelegate()
{
	InteractionKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnInteractKeySelected);
	ForwardKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnForwardKeySelected);
	BackwardKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnBackwardKeySelected);
	RightKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnRightKeySelected);
	LeftKeySelector->OnKeySelected.AddDynamic(this, &UOptionsWidget::OnLeftKeySelected);

	ReturnBtn->OnClicked.AddDynamic(this, &UOptionsWidget::Return);
	ErrorKeyBtn->OnClicked.AddDynamic(this, &UOptionsWidget::DisableErrorCanvas);
}

void UOptionsWidget::Return()
{
	InputSettings->SaveKeyMappings();
	
	AGameHUD* GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	check(GameHUD != nullptr);
	GameHUD->BackToPauseMenu();
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
		InputSettings->RemoveAxisMapping(GetAxisMappingPositive(MappingName[1]));
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
		InputSettings->RemoveAxisMapping(GetAxisMappingNegative(MappingName[1]));
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
		InputSettings->RemoveAxisMapping(GetAxisMappingPositive(MappingName[2]));
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
		InputSettings->RemoveAxisMapping(GetAxisMappingNegative(MappingName[2]));
		InputSettings->AddAxisMapping(FInputAxisKeyMapping(static_cast<FName>(MappingName[2]), InputChord.Key, NegativeScale));	
	}
}
#pragma endregion 

#pragma region GetAction/AxisMapping
FInputActionKeyMapping UOptionsWidget::GetActionMapping(const FString &KeyName) const
{
	TArray<FInputActionKeyMapping> OutMappings;
	InputSettings->GetActionMappingByName(static_cast<FName>(KeyName), OutMappings);

	return OutMappings[0];
}

FInputAxisKeyMapping UOptionsWidget::GetAxisMappingPositive(const FString &KeyName) const
{
	TArray<FInputAxisKeyMapping> OutMappings;
	InputSettings->GetAxisMappingByName(static_cast<FName>(KeyName), OutMappings);

	FInputAxisKeyMapping KeyMapping;
	
	for (const auto Mapping : OutMappings)
	{
		if (Mapping.Scale > 0)
		{
			KeyMapping = Mapping;
			break;
		}
	}

	return KeyMapping;
}

FInputAxisKeyMapping UOptionsWidget::GetAxisMappingNegative(const FString& KeyName) const
{
	TArray<FInputAxisKeyMapping> OutMappings;
	InputSettings->GetAxisMappingByName(static_cast<FName>(KeyName), OutMappings);

	FInputAxisKeyMapping KeyMapping;
	
	for (const auto Mapping : OutMappings)
	{
		if (Mapping.Scale < 0)
		{
			KeyMapping = Mapping;
			break;
		}
	}

	return KeyMapping;
}
#pragma endregion

#pragma region ErrorKey
bool UOptionsWidget::IsAvailableKey(const FKey &Key)
{
	InputSettings = UInputSettings::GetInputSettings();
	bool bFind = false;
	
	for (auto ActionKeyMapping : InputSettings->GetActionMappings())
	{
		if (ActionKeyMapping.Key.GetFName() == Key.GetFName())
		{
			bFind = true;
			break;
		}	
	}

	for (auto AxisKeyMapping : InputSettings->GetAxisMappings())
	{
		if (AxisKeyMapping.Key.GetFName() == Key.GetFName())
		{
			bFind = true;
			break;
		}
	}

	return bFind;
}

void UOptionsWidget::ErrorKey(const FString NameMapping, const bool bPositiveScale)
{
	CanvasPanelErrorKey->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (NameMapping == MappingName[0])
	{
		InteractionKeySelector->SetSelectedKey(GetActionMapping(NameMapping).Key);
	}
	else if (NameMapping == MappingName[1])
	{
		if (bPositiveScale)
			ForwardKeySelector->SetSelectedKey(GetAxisMappingPositive(NameMapping).Key);
		else
			BackwardKeySelector->SetSelectedKey(GetAxisMappingNegative(NameMapping).Key);
	}
	else if (NameMapping == MappingName[2])
	{
		if (bPositiveScale)
			RightKeySelector->SetSelectedKey(GetAxisMappingPositive(NameMapping).Key);
		else
			LeftKeySelector->SetSelectedKey(GetAxisMappingNegative(NameMapping).Key);
	}
}
#pragma endregion