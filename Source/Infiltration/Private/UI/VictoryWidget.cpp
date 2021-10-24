// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/VictoryWidget.h"

#include "Components/Button.h"
#include "Infiltration/InfiltrationGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UVictoryWidget::UVictoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UVictoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RestartBtn->OnClicked.AddDynamic(this, &UVictoryWidget::RestartGame);
	QuitBtn->OnClicked.AddDynamic(this, &UVictoryWidget::QuitGame);
}

void UVictoryWidget::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UVictoryWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
