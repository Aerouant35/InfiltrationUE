// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefeatWidget.h"
#include "OptionsWidget.h"
#include "PauseWidget.h"
#include "PlayerWidget.h"
#include "VictoryWidget.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
	#pragma region WidgetVariables
	UPROPERTY()
	class UPlayerWidget* PlayerWidget;
	
	UPROPERTY()
	class UVictoryWidget* VictoryWidget;
	
	UPROPERTY()
	class UDefeatWidget* DefeatWidget;
	
	UPROPERTY()
	class UPauseWidget* PauseWidget;
	
	UPROPERTY()
	class UOptionsWidget* OptionsWidget;
	#pragma endregion
	
	#pragma region WidgetClassVariables
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UUserWidget> PlayerWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UVictoryWidget> VictoryWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UDefeatWidget> DefeatWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UPauseWidget> PauseWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UOptionsWidget> OptionsWidgetClass;
	#pragma endregion
	
public:
	AGameHUD();

protected:
	virtual void BeginPlay() override;

	void InitWidget();
	
	void EnableMouseCursor(const bool bEnable) const;

public:
	/** Update progress bar percent in Player UI.
	 * @param	CurrentNbFood				Uint8 current number food.
	 */
	UFUNCTION()
	void UpdateProgressBarPercent(const uint8 CurrentNbFood) const;

	#pragma region ToDisplayMethod
	UFUNCTION()
	void ShowVictoryScreen() const;

	UFUNCTION()
	void ShowDefeatScreen() const;

	UFUNCTION()
	void ShowPauseScreen() const;

	UFUNCTION()
	void ResumeGame() const;

	UFUNCTION()
	void OptionsMenu() const;

	UFUNCTION()
	void BackToPauseMenu() const;
	#pragma endregion 
};
