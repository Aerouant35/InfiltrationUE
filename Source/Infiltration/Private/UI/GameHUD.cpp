// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"

#include "Infiltration/InfiltrationGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

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
	
	if (!PlayerWidget) return;
	EnableMouseCursor(false);
	PlayerWidget->UpdateProgressBarPercent(0);
	PlayerWidget->AddToViewport();
}

void AGameHUD::EnableMouseCursor(const bool bEnable) const
{
	APlayerController* MyController = UGameplayStatics::GetPlayerController(this, 0);
	
	MyController->bShowMouseCursor = bEnable;
	MyController->bEnableClickEvents = bEnable;
	MyController->bEnableMouseOverEvents = bEnable;
}

void AGameHUD::UpdateProgressBarPercent(const float Percent) const
{
	if (!PlayerWidget) return;
	PlayerWidget->UpdateProgressBarPercent(Percent / Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->GetNbFoodWin());
}

void AGameHUD::ShowVictoryScreen() const
{
	if (!VictoryWidget) return;
	EnableMouseCursor(true);

	PlayerWidget->RemoveFromViewport();
	VictoryWidget->AddToViewport();
}

void AGameHUD::ShowDefeatScreen() const
{
	if (!DefeatWidget) return;
	EnableMouseCursor(true);
	
	PlayerWidget->RemoveFromViewport();
	DefeatWidget->AddToViewport();
}

void AGameHUD::ShowPauseScreen()
{
	if (PauseWidget == nullptr) return;
	EnableMouseCursor(true);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	
	PlayerWidget->RemoveFromViewport();
	PauseWidget->AddToViewport();
}

void AGameHUD::ResumeGame()
{
	if (PauseWidget == nullptr) return;
	EnableMouseCursor(false);
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	PauseWidget->RemoveFromViewport();
	PlayerWidget->AddToViewport();
}
