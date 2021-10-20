// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuHUD.h"

AMainMenuHUD::AMainMenuHUD()
{
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	}
	
	if (!MainMenuWidget) return;
	
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
 
	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;
	MyController->bEnableMouseOverEvents = true;
	
	MainMenuWidget->AddToViewport();
}
