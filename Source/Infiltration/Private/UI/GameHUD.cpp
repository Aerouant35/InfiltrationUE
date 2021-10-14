// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
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
	
	if (!PlayerWidget) return;
	EnableMouseCursor(false);
	PlayerWidget->UpdateProgressBarPercent(0);
	PlayerWidget->AddToViewport();
}

void AGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameHUD::EnableMouseCursor(const bool bEnable) const
{
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
 
	MyController->bShowMouseCursor = bEnable;
	MyController->bEnableClickEvents = bEnable;
	MyController->bEnableMouseOverEvents = bEnable;
}

void AGameHUD::UpdateProgressBarPercent(const float Percent) const
{
	if (!PlayerWidget) return;
	PlayerWidget->UpdateProgressBarPercent(Percent);
}

void AGameHUD::ShowVictory() const
{
	if (!VictoryWidget) return;
	EnableMouseCursor(true);
	VictoryWidget->AddToViewport();
}

void AGameHUD::ShowDefeat() const
{
	if (!DefeatWidget) return;
	EnableMouseCursor(true);
	DefeatWidget->AddToViewport();
}