// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/MainMenuWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
	HowToBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::HowToPlayDisplay);
	OptionsBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OptionsDisplay);
	CreditBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::CreditDisplay);
	QuitBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
}

#pragma region ButtonMethod

void UMainMenuWidget::PlayGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Dungeon")));
}

void UMainMenuWidget::HowToPlayDisplay()
{
	Cast<AMainMenuHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->HowToPlayDisplay();
}

void UMainMenuWidget::OptionsDisplay()
{
	Cast<AMainMenuHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->OptionsDisplay();
}

void UMainMenuWidget::CreditDisplay()
{
	Cast<AMainMenuHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->CreditsDisplay();
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
#pragma endregion