// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DefeatWidget.h"

#include "Kismet/KismetSystemLibrary.h"

UDefeatWidget::UDefeatWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDefeatWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDefeatWidget::RestartGame()
{
}

void UDefeatWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
