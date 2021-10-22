// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DefeatWidget.h"

#include "Components/Button.h"
#include "Infiltration/InfiltrationGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

UDefeatWidget::UDefeatWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDefeatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RestartBtn->OnClicked.AddDynamic(this, &UDefeatWidget::RestartGame);
	QuitBtn->OnClicked.AddDynamic(this, &UDefeatWidget::QuitGame);
}

void UDefeatWidget::RestartGame()
{
	Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->ResetLevel();
}

void UDefeatWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
