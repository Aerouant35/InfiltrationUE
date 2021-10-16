// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefeatWidget.h"
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

	UPlayerWidget* PlayerWidget;
	UVictoryWidget* VictoryWidget;
	UDefeatWidget* DefeatWidget;

	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UUserWidget> PlayerWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UVictoryWidget> VictoryWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widget")
	TSubclassOf<UDefeatWidget> DefeatWidgetClass;
	
public:
	AGameHUD();

protected:
	virtual void BeginPlay() override;
	
	void EnableMouseCursor(const bool bEnable) const;

public:
	/** Update progress bar percent in Player UI.
	 * @param	Percent					Float range between 0 and 1.
	 */
	UFUNCTION()
	void UpdateProgressBarPercent(const float Percent) const;

	UFUNCTION()
	void ShowVictoryScreen() const;

	UFUNCTION()
	void ShowDefeatScreen() const;
};
