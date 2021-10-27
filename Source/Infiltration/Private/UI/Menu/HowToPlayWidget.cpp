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

void UHowToPlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UHowToPlayWidget::Return()
{
	Cast<AMainMenuHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD())->HowToPlayToMainMenu();
}
