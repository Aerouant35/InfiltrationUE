// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/MainMenuHUD.h"

AMainMenuHUD::AMainMenuHUD()
{
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	InitWidget();
	
	if (!MainMenuWidget) return;
	
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
 
	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;
	MyController->bEnableMouseOverEvents = true;
	
	MainMenuWidget->AddToViewport();
}

void AMainMenuHUD::InitWidget()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	}

	if (HowToPlayWidgetClass)
	{
		HowToPlayWidget = CreateWidget<UHowToPlayWidget>(GetWorld(), HowToPlayWidgetClass);
	}
	
	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UMenuOptionsWidget>(GetWorld(), OptionsWidgetClass);
	}
	
	if (CreditsWidgetClass)
	{
		CreditWidget = CreateWidget<UCreditsWidget>(GetWorld(), CreditsWidgetClass);
	}
}

#pragma region ToDisplayMethod
void AMainMenuHUD::HowToPlayDisplay()
{
	if (!HowToPlayWidget && !MainMenuWidget) return;
	if (HowToPlayWidget->IsInViewport()) return;

	MainMenuWidget->RemoveFromViewport();
	HowToPlayWidget->AddToViewport();
}

void AMainMenuHUD::OptionsDisplay()
{
	if (!OptionsWidget && !MainMenuWidget) return;
	if (OptionsWidget->IsInViewport()) return;

	MainMenuWidget->RemoveFromViewport();
	OptionsWidget->AddToViewport();
}

void AMainMenuHUD::CreditsDisplay()
{
	if (!CreditWidget && !MainMenuWidget) return;
	if (CreditWidget->IsInViewport()) return;

	MainMenuWidget->RemoveFromViewport();
	CreditWidget->AddToViewport();
}
#pragma endregion 

#pragma region BackToMenuMethod
void AMainMenuHUD::HowToPlayToMainMenu()
{
	if (!HowToPlayWidget && !MainMenuWidget) return;
	if (MainMenuWidget->IsInViewport()) return;
	
	HowToPlayWidget->RemoveFromViewport();
	MainMenuWidget->AddToViewport();
}

void AMainMenuHUD::OptionsToMainMenu()
{
	if (!OptionsWidget && !MainMenuWidget) return;
	if (MainMenuWidget->IsInViewport()) return;
	
	OptionsWidget->RemoveFromViewport();
	MainMenuWidget->AddToViewport();
}

void AMainMenuHUD::CreditsToMainMenu()
{
	if (!CreditWidget && !MainMenuWidget) return;
	if (MainMenuWidget->IsInViewport()) return;
	
	CreditWidget->RemoveFromViewport();
	MainMenuWidget->AddToViewport();
}
#pragma endregion 
