// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DefeatWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UDefeatWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RestartBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitBtn;
	
public:
	UDefeatWidget(const FObjectInitializer& ObjectInitializer);

private:
	virtual void NativeConstruct() override;

public:
	void RestartGame();

	void QuitGame();
};