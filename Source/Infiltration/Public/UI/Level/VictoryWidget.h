// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VictoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UVictoryWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RestartBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitBtn;
	
public:
	UVictoryWidget(const FObjectInitializer& ObjectInitializer);

	void InitDelegate();
private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
		void RestartGame();
	UFUNCTION()
		void QuitGame();
};
