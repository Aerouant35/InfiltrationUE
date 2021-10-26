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

	if (!PlayerWidget) return;
	EnableMouseCursor(false);
	PlayerWidget->UpdateProgressBarPercent(0);
	PlayerWidget->AddToViewport();
}

void AGameHUD::InitWidget()
{
	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
	}

	if (VictoryWidgetClass)
	{
		VictoryWidget = CreateWidget<UVictoryWidget>(GetWorld(), VictoryWidgetClass);
	}

	if (DefeatWidgetClass)
	{
		DefeatWidget = CreateWidget<UDefeatWidget>(GetWorld(), DefeatWidgetClass);
	}

	if (PauseWidgetClass)
	{
		PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
	}

	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UOptionsWidget>(GetWorld(), OptionsWidgetClass);
	}
}

void AGameHUD::EnableMouseCursor(const bool bEnable) const
{
	APlayerController* MyController = UGameplayStatics::GetPlayerController(this, 0);

	MyController->bShowMouseCursor = bEnable;
	MyController->bEnableClickEvents = bEnable;
	MyController->bEnableMouseOverEvents = bEnable;

	if (bEnable)
	{
		FInputModeUIOnly InputModeUIOnly;
		InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
		MyController->SetInputMode(InputModeUIOnly);
	}
	else
	{
		FInputModeGameOnly InputModeGameOnly;
		MyController->SetInputMode(InputModeGameOnly);
	}
}

void AGameHUD::UpdateProgressBarPercent(const float Percent) const
{
	if (!PlayerWidget) return;
	PlayerWidget->UpdateProgressBarPercent(Percent / Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->GetNbFoodWin());
}

void AGameHUD::ShowVictoryScreen() const
{
	if (!VictoryWidget) return;
	if (VictoryWidget->IsInViewport()) return;

	EnableMouseCursor(true);

	PlayerWidget->RemoveFromViewport();
	VictoryWidget->AddToViewport();
}

void AGameHUD::ShowDefeatScreen() const
{
	if (!DefeatWidget) return;
	if (DefeatWidget->IsInViewport()) return;

	EnableMouseCursor(true);

	PlayerWidget->RemoveFromViewport();
	DefeatWidget->AddToViewport();
}

void AGameHUD::ShowPauseScreen()
{
	if (!PauseWidget) return;
	if (PauseWidget->IsInViewport()) return;

	EnableMouseCursor(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	PlayerWidget->RemoveFromViewport();
	PauseWidget->AddToViewport();
}

void AGameHUD::ResumeGame()
{
	if (!PauseWidget) return;
	if (PlayerWidget->IsInViewport()) return;

	EnableMouseCursor(false);
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	PauseWidget->RemoveFromViewport();
	PlayerWidget->AddToViewport();
}

void AGameHUD::OptionsMenu()
{
	if (!OptionsWidget && !PauseWidget) return;
	if (OptionsWidget->IsInViewport()) return;

	PauseWidget->RemoveFromViewport();
	OptionsWidget->AddToViewport();
}

void AGameHUD::BackToPauseMenu()
{
	if (!OptionsWidget && !PauseWidget) return;
	if (PauseWidget->IsInViewport()) return;
	
	OptionsWidget->RemoveFromViewport();
	PauseWidget->AddToViewport();
}
