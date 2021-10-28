// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HowToPlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UHowToPlayWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ReturnBtn;

public:
	UHowToPlayWidget(const FObjectInitializer& ObjectInitializer);

	void InitDelegate();
	
private:
	UFUNCTION()
	void Return();
};
