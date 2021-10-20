// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* PlayBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* HowToBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreditBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitBtn;

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void QuitGame();
};
