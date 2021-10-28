// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/MenuOptionsWidget.h"
#include "Components/Button.h"
#include "Components/InputKeySelector.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Menu/MainMenuHUD.h"

UMenuOptionsWidget::UMenuOptionsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UMenuOptionsWidget::InitDelegate()
{
	InteractionKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnInteractKeySelected);
	ForwardKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnForwardKeySelected);
	BackwardKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnBackwardKeySelected);
	RightKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnRightKeySelected);
	LeftKeySelector->OnKeySelected.AddDynamic(this, &UMenuOptionsWidget::OnLeftKeySelected);

	ReturnBtn->OnClicked.AddDynamic(this, &UMenuOptionsWidget::Return);
	ErrorKeyBtn->OnClicked.AddDynamic(this, &UMenuOptionsWidget::DisableErrorCanvas);
}

void UMenuOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InputSettings = UInputSettings::GetInputSettings();
	check(InputSettings != nullptr);
	
	InteractionKeySelector->SetSelectedKey(GetActionMapping(MappingName[0]).Key);
	ForwardKeySelector->SetSelectedKey(GetAxisMappingPositive(MappingName[1]).Key);
	BackwardKeySelector->SetSelectedKey(GetAxisMappingPositive(MappingName[1]).Key);
	RightKeySelector->SetSelectedKey(GetAxisMappingPositive(MappingName[2]).Key);
	LeftKeySelector->SetSelectedKey(GetAxisMappingPositive(MappingName[2]).Key);

	DisableErrorCanvas();
}

void UMenuOptionsWidget::Return()
{
	InputSettings->SaveKeyMappings();
	
	AMainMenuHUD* MainMenuHUD = Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	check(MainMenuHUD != nullptr);
	MainMenuHUD->OptionsToMainMenu();
}

#pragma region KeyRebindButton
void UMenuOptionsWidget::OnInteractKeySelected(const FInputChord InputChord)
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

void UMenuOptionsWidget::OnForwardKeySelected(const FInputChord InputChord)
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

void UMenuOptionsWidget::OnBackwardKeySelected(const FInputChord InputChord)
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

void UMenuOptionsWidget::OnRightKeySelected(const FInputChord InputChord)
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

void UMenuOptionsWidget::OnLeftKeySelected(const FInputChord InputChord)
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

#pragma region GetAction/AxisMapping=
FInputActionKeyMapping UMenuOptionsWidget::GetActionMapping(const FString& KeyName) const
{
	TArray<FInputActionKeyMapping> OutMappings;
	InputSettings->GetActionMappingByName(static_cast<FName>(KeyName), OutMappings);

	return OutMappings[0];
}

FInputAxisKeyMapping UMenuOptionsWidget::GetAxisMappingPositive(const FString& KeyName) const
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

FInputAxisKeyMapping UMenuOptionsWidget::GetAxisMappingNegative(const FString& KeyName) const
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
bool UMenuOptionsWidget::IsAvailableKey(const FKey &Key)
{
	InputSettings = UInputSettings::GetInputSettings();
	check(InputSettings != nullptr);

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

void UMenuOptionsWidget::ErrorKey(const FString NameMapping, const bool bPositiveScale)
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
