// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/CreditsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Menu/MainMenuHUD.h"

UCreditsWidget::UCreditsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCreditsWidget::InitDelegate()
{
	ReturnBtn->OnClicked.AddDynamic(this, &UCreditsWidget::Return);
}

void UCreditsWidget::Return()
{
	AMainMenuHUD* MainMenuHUD = Cast<AMainMenuHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	check(MainMenuHUD != nullptr);
	MainMenuHUD->CreditsToMainMenu();
}
