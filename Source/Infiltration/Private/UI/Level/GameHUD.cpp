// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Level/GameHUD.h"
#include "Infiltration/InfiltrationGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	InitWidget();

	EnableMouseCursor(false);
	PlayerWidget->UpdateProgressBarPercent(0);
	PlayerWidget->AddToViewport();
}

void AGameHUD::InitWidget()
{
	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		check(PlayerWidget != nullptr);
	}

	if (VictoryWidgetClass)
	{
		VictoryWidget = CreateWidget<UVictoryWidget>(GetWorld(), VictoryWidgetClass);
		check(VictoryWidget != nullptr);
		VictoryWidget->InitDelegate();
	}

	if (DefeatWidgetClass)
	{
		DefeatWidget = CreateWidget<UDefeatWidget>(GetWorld(), DefeatWidgetClass);
		check(DefeatWidget != nullptr);
		DefeatWidget->InitDelegate();
	}

	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
		check(PauseWidget != nullptr);
		PauseWidget->InitDelegate();
	}

	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UOptionsWidget>(GetWorld(), OptionsWidgetClass);
		check(OptionsWidget != nullptr);
		OptionsWidget->InitDelegate();
	}
}

void AGameHUD::EnableMouseCursor(const bool bEnable) const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	check(PlayerController != nullptr);
	
	PlayerController->bShowMouseCursor = bEnable;
	PlayerController->bEnableClickEvents = bEnable;
	PlayerController->bEnableMouseOverEvents = bEnable;

	if (bEnable)
	{
		FInputModeUIOnly InputModeUIOnly;
		InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
		PlayerController->SetInputMode(InputModeUIOnly);
	}
	else
	{
		FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
	}
}

void AGameHUD::UpdateProgressBarPercent(const uint8 CurrentNbFood) const
{
	check(PlayerWidget != nullptr);

	AInfiltrationGameModeBase* InGameMode = Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode());
	check(InGameMode != nullptr);

	PlayerWidget->UpdateProgressBarPercent(CurrentNbFood / static_cast<float>(InGameMode->GetNbFoodWin()));
}

void AGameHUD::ShowVictoryScreen() const
{
	check(VictoryWidget != nullptr && PlayerWidget != nullptr);
	if (VictoryWidget->IsInViewport()) return;

	EnableMouseCursor(true);

	PlayerWidget->RemoveFromViewport();
	VictoryWidget->AddToViewport();
}

void AGameHUD::ShowDefeatScreen() const
{
	check(DefeatWidget != nullptr && PlayerWidget != nullptr);
	if (DefeatWidget->IsInViewport()) return;

	EnableMouseCursor(true);

	PlayerWidget->RemoveFromViewport();
	DefeatWidget->AddToViewport();
}

void AGameHUD::ShowPauseScreen() const
{
	check(PauseWidget != nullptr && PlayerWidget != nullptr);
	if (PauseWidget->IsInViewport()) return;

	EnableMouseCursor(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	PlayerWidget->RemoveFromViewport();
	PauseWidget->AddToViewport();
}

void AGameHUD::ResumeGame() const
{
	check(PauseWidget != nullptr && PlayerWidget != nullptr);
	if (PlayerWidget->IsInViewport()) return;

	EnableMouseCursor(false);
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	PauseWidget->RemoveFromViewport();
	PlayerWidget->AddToViewport();
}

void AGameHUD::OptionsMenu() const
{
	check(PauseWidget != nullptr && OptionsWidget != nullptr);
	if (OptionsWidget->IsInViewport()) return;

	PauseWidget->RemoveFromViewport();
	OptionsWidget->AddToViewport();
}

void AGameHUD::BackToPauseMenu() const
{
	check(OptionsWidget != nullptr && PlayerWidget != nullptr);
	if (PauseWidget->IsInViewport()) return;
	
	OptionsWidget->RemoveFromViewport();
	PauseWidget->AddToViewport();
}
