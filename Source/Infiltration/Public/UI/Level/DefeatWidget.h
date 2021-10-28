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

	#pragma region Variables
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RestartBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitBtn;
	#pragma endregion
	
public:
	UDefeatWidget(const FObjectInitializer& ObjectInitializer);

	void InitDelegate();
	
	UFUNCTION()
	void RestartGame();
	
	UFUNCTION()
	void QuitGame();
};
