// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
	QuitBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);

	//TODO: Do "How to play" widget and "Credit" widget
}

void UMainMenuWidget::PlayGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Dungeon")));
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
