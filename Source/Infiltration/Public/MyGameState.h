// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	uint8 NumberOfFoods;

public:

	AMyGameState();

	UFUNCTION()
	void IncrementFood();

	UFUNCTION()
	void DecrementFood();

	UFUNCTION()
	FORCEINLINE uint8 GetNumberOfFoods() const { return NumberOfFoods; };
};
