// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainMenuWidget.h"
#include "MenuOptionsWidget.h"
#include "CreditsWidget.h"
#include "HowToPlayWidget.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

#pragma region WidgetVariables
	UPROPERTY()
	class UMainMenuWidget* MainMenuWidget;
	
	UPROPERTY()
	class UMenuOptionsWidget* OptionsWidget;

	UPROPERTY()
	class UCreditsWidget* CreditWidget;
	
	UPROPERTY()
	class UHowToPlayWidget* HowToPlayWidget;
#pragma endregion 

#pragma region WidgetClassVariables
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UMenuOptionsWidget> OptionsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UCreditsWidget> CreditsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UHowToPlayWidget> HowToPlayWidgetClass;
#pragma endregion 
	
public:
	AMainMenuHUD();

protected:
	virtual void BeginPlay() override;

	void InitWidget();

public:
#pragma region ToDisplayMethod
	UFUNCTION()
	void OptionsDisplay();

	UFUNCTION()
	void HowToPlayDisplay();

	UFUNCTION()
	void CreditsDisplay();
#pragma endregion
	
#pragma region BackToMenuMethod
	UFUNCTION()
	void HowToPlayToMainMenu();
	
	UFUNCTION()
	void OptionsToMainMenu();

	UFUNCTION()
	void CreditsToMainMenu();
#pragma endregion 
};
