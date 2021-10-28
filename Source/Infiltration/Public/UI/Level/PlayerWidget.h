// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* FoodProgress;
	
public:
	UPlayerWidget(const FObjectInitializer& ObjectInitializer);
	
	/** Update progress bar percent in Player UI.
	 * @param	Percent					Float range between 0 and 1.
	 */
	void UpdateProgressBarPercent(const float Percent) const;
};
