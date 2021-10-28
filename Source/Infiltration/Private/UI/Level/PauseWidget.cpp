// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Level/PauseWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

UPauseWidget::UPauseWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPauseWidget::InitDelegate()
{
	ResumeBtn->OnClicked.AddDynamic(this, &UPauseWidget::ResumeGame);
	OptionsBtn->OnClicked.AddDynamic(this, &UPauseWidget::OptionsMenu);
	MenuBtn->OnClicked.AddDynamic(this, &UPauseWidget::BackToMenu);
	QuitBtn->OnClicked.AddDynamic(this, &UPauseWidget::QuitGame);

	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	check(GameHUD != nullptr);
}

#pragma region ButtonMethod
void UPauseWidget::ResumeGame()
{
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->ResumeGame();
}

void UPauseWidget::OptionsMenu()
{
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->OptionsMenu();
}

void UPauseWidget::BackToMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("MainMenu")));
}

void UPauseWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
#pragma endregion 
