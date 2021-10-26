// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Menu/MainMenuHUD.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

#pragma region Variables
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* PlayBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* HowToBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OptionsBtn;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CreditBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitBtn;
#pragma endregion 

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

private:
	virtual void NativeConstruct() override;

#pragma region ButtonMethod
	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void HowToPlayDisplay();

	UFUNCTION()
	void OptionsDisplay();

	UFUNCTION()
	void CreditDisplay();

	UFUNCTION()
	void QuitGame();
#pragma endregion 
};
