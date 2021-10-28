// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Level/GameHUD.h"
#include "PauseWidget.generated.h"

/**	
 * 
 */
UCLASS()
class INFILTRATION_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

	#pragma region Variables
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ResumeBtn;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OptionsBtn;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MenuBtn;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitBtn;

	UPROPERTY()
	class AGameHUD* GameHUD;
	#pragma endregion 
	
public:
	UPauseWidget(const FObjectInitializer& ObjectInitializer);

	void InitDelegate();

	#pragma region ButtonMethod
	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void OptionsMenu();
	
	UFUNCTION()
	void BackToMenu();

	UFUNCTION()
	void QuitGame();
	#pragma endregion 
};
