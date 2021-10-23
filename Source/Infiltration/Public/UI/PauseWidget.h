// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/GameHUD.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ResumeBtn;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OptionsBtn;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MenuBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitBtn;
	
public:
	UPauseWidget(const FObjectInitializer& ObjectInitializer);

private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void OptionsMenu();
	
	UFUNCTION()
	void BackToMenu();

	UFUNCTION()
	void QuitGame();
};
