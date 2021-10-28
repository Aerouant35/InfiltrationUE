// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/MainMenuHUD.h"

AMainMenuHUD::AMainMenuHUD()
{
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	InitWidget();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	check(PlayerController != nullptr);
	
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
	PlayerController->bEnableMouseOverEvents = true;

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	PlayerController->SetInputMode(InputModeUIOnly);
	
	MainMenuWidget->AddToViewport();
}

void AMainMenuHUD::InitWidget()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		check(MainMenuWidget != nullptr);

		MainMenuWidget->InitDelegate();
	}

	if (HowToPlayWidgetClass)
	{
		HowToPlayWidget = CreateWidget<UHowToPlayWidget>(GetWorld(), HowToPlayWidgetClass);
		check(HowToPlayWidget != nullptr);

		HowToPlayWidget->InitDelegate();
	}
	
	if (OptionsWidgetClass)
	{
		OptionsWidget = CreateWidget<UMenuOptionsWidget>(GetWorld(), OptionsWidgetClass);
		check(OptionsWidget != nullptr);

		OptionsWidget->InitDelegate();
	}
	
	if (CreditsWidgetClass)
	{
		CreditWidget = CreateWidget<UCreditsWidget>(GetWorld(), CreditsWidgetClass);
		check(CreditWidget != nullptr);

		CreditWidget->InitDelegate();
	}
}

#pragma region ToDisplayMethod
void AMainMenuHUD::HowToPlayDisplay()
{
	check(HowToPlayWidget != nullptr && MainMenuWidget != nullptr);
	if (HowToPlayWidget->IsInViewport()) return;

	MainMenuWidget->RemoveFromViewport();
	HowToPlayWidget->AddToViewport();
}

void AMainMenuHUD::OptionsDisplay()
{
	check(OptionsWidget != nullptr && MainMenuWidget != nullptr);
	if (OptionsWidget->IsInViewport()) return;

	MainMenuWidget->RemoveFromViewport();
	OptionsWidget->AddToViewport();
}

void AMainMenuHUD::CreditsDisplay()
{
	check(CreditWidget != nullptr && MainMenuWidget != nullptr);
	if (CreditWidget->IsInViewport()) return;

	MainMenuWidget->RemoveFromViewport();
	CreditWidget->AddToViewport();
}
#pragma endregion 

#pragma region BackToMenuMethod
void AMainMenuHUD::HowToPlayToMainMenu()
{
	check(HowToPlayWidget != nullptr && MainMenuWidget != nullptr);
	if (MainMenuWidget->IsInViewport()) return;
	
	HowToPlayWidget->RemoveFromViewport();
	MainMenuWidget->AddToViewport();
}

void AMainMenuHUD::OptionsToMainMenu()
{
	check(OptionsWidget != nullptr && MainMenuWidget != nullptr);
	if (MainMenuWidget->IsInViewport()) return;
	
	OptionsWidget->RemoveFromViewport();
	MainMenuWidget->AddToViewport();
}

void AMainMenuHUD::CreditsToMainMenu()
{
	check(CreditWidget != nullptr && MainMenuWidget != nullptr);
	if (MainMenuWidget->IsInViewport()) return;
	
	CreditWidget->RemoveFromViewport();
	MainMenuWidget->AddToViewport();
}
#pragma endregion 
