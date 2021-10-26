// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "GameFramework/InputSettings.h"
#include "MenuOptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UMenuOptionsWidget : public UUserWidget
{
	GENERATED_BODY()
	
	const FString MappingName[3] {TEXT("Interact"), TEXT("MoveForward"), TEXT("MoveRight")};
    	
    const short PositiveScale = 1;
    const short NegativeScale = -1;

    UPROPERTY()
    UInputSettings* InputSettings;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UInputKeySelector* ForwardKeySelector;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UInputKeySelector* BackwardKeySelector;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UInputKeySelector* LeftKeySelector;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UInputKeySelector* RightKeySelector;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UInputKeySelector* InteractionKeySelector;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UButton* ReturnBtn;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UCanvasPanel* CanvasPanelErrorKey;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UButton* ErrorKeyBtn;

public:
	UMenuOptionsWidget(const FObjectInitializer& ObjectInitializer);

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Return();
	
	UFUNCTION()
	FInputActionKeyMapping GetActionMapping(FString KeyName) const;

	UFUNCTION()
	FInputAxisKeyMapping GetAxisMapping(FString KeyName, bool bPositiveScale) const;

	UFUNCTION()
	void OnInteractKeySelected(FInputChord InputChord);
	
	UFUNCTION()
	void OnForwardKeySelected(FInputChord InputChord);
	
	UFUNCTION()
	void OnBackwardKeySelected(FInputChord InputChord);
	
	UFUNCTION()
	void OnRightKeySelected(FInputChord InputChord);
	
	UFUNCTION()
	void OnLeftKeySelected(FInputChord InputChord);
	
	UFUNCTION()
	bool IsAvailableKey(FKey Key);

	UFUNCTION()
	void ErrorKey(FString NameMapping, bool bPositiveScale = true) const;

	UFUNCTION()
	void DisableErrorCanvas()
	{
		CanvasPanelErrorKey->SetVisibility(ESlateVisibility::Hidden);
	}
};
