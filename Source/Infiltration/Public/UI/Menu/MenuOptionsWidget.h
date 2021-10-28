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

	#pragma region ConstVariables
	const FString MappingName[3] {TEXT("Interact"), TEXT("MoveForward"), TEXT("MoveRight")};
    	
    const short PositiveScale = 1;
    const short NegativeScale = -1;
	#pragma endregion 

	#pragma region Variables
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
	#pragma endregion 

public:
	UMenuOptionsWidget(const FObjectInitializer& ObjectInitializer);

	void InitDelegate();
private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Return();

	#pragma region KeyRebindButton
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
	#pragma endregion 

	#pragma region GetAction/AxisMapping
	UFUNCTION()
	FInputActionKeyMapping GetActionMapping(const FString &KeyName) const;

	UFUNCTION()
	FInputAxisKeyMapping GetAxisMappingPositive(const FString &KeyName) const;
	
	UFUNCTION()
	FInputAxisKeyMapping GetAxisMappingNegative(const FString &KeyName) const;

	#pragma endregion 

	#pragma region ErrorKey
	UFUNCTION()
	bool IsAvailableKey(const FKey &Key);

	UFUNCTION()
	void ErrorKey(FString NameMapping, bool bPositiveScale = true);

	UFUNCTION()
	void DisableErrorCanvas()
	{
		CanvasPanelErrorKey->SetVisibility(ESlateVisibility::Hidden);
	}
	#pragma endregion 
};
