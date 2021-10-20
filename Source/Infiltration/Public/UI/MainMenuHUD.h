// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMenuWidget.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
	UMainMenuWidget* MainMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

public:
	AMainMenuHUD();

protected:
	virtual void BeginPlay() override;

};
