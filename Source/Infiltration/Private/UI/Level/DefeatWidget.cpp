// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Level/DefeatWidget.h"

#include "Components/Button.h"
#include "Infiltration/InfiltrationGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UDefeatWidget::UDefeatWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDefeatWidget::InitDelegate()
{
	RestartBtn->OnClicked.AddDynamic(this, &UDefeatWidget::RestartGame);
	QuitBtn->OnClicked.AddDynamic(this, &UDefeatWidget::QuitGame);
}

void UDefeatWidget::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()), false);
}

void UDefeatWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
