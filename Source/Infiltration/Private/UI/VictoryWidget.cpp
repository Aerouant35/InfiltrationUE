// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VictoryWidget.h"

#include "Infiltration/InfiltrationGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

UVictoryWidget::UVictoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UVictoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UVictoryWidget::RestartGame()
{
	Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->ResetLevel();
}

void UVictoryWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
