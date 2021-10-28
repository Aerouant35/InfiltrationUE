// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/HowToPlayWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Menu/MainMenuHUD.h"

UHowToPlayWidget::UHowToPlayWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHowToPlayWidget::InitDelegate()
{
	ReturnBtn->OnClicked.AddDynamic(this, &UHowToPlayWidget::Return);
}

void UHowToPlayWidget::Return()
{
	AMainMenuHUD* MainMenuHUD = Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	check(MainMenuHUD != nullptr);
	MainMenuHUD->HowToPlayToMainMenu();
}
