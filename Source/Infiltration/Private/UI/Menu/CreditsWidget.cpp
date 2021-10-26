// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/CreditsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Menu/MainMenuHUD.h"

UCreditsWidget::UCreditsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCreditsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReturnBtn->OnClicked.AddDynamic(this, &UCreditsWidget::Return);
}

void UCreditsWidget::Return()
{
	Cast<AMainMenuHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->CreditsToMainMenu();
}
