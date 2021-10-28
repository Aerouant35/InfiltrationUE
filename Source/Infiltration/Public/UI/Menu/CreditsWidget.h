// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ReturnBtn;

public:
	UCreditsWidget(const FObjectInitializer& ObjectInitializer);

	void InitDelegate();
	
private:
	UFUNCTION()
	void Return();
};
