// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VictoryWidget.h"

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
}

void UVictoryWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
