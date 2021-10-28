// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMainMenuWidget::InitDelegate()
{
	PlayBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
	HowToBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::HowToPlayDisplay);
	OptionsBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OptionsDisplay);
	CreditBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::CreditDisplay);
	QuitBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);

	MainMenuHUD = Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	check(MainMenuHUD != nullptr);
}

#pragma region ButtonMethod
void UMainMenuWidget::PlayGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Level1")));
}

void UMainMenuWidget::HowToPlayDisplay()
{
	MainMenuHUD->HowToPlayDisplay();
}

void UMainMenuWidget::OptionsDisplay()
{
	MainMenuHUD->OptionsDisplay();
}

void UMainMenuWidget::CreditDisplay()
{
	MainMenuHUD->CreditsDisplay();
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
#pragma endregion