// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InfiltrationGameState.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AInfiltrationGameState : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	uint8 NumberOfFoods;

	UPROPERTY(VisibleAnywhere)
	uint8 NumberOfEnemys;

public:

	AInfiltrationGameState();

	UFUNCTION()
	void IncrementNumberOfFoods();

	UFUNCTION()
	void DecrementNumberOfFoods();

	UFUNCTION()
	void IncrementNumberOfEnemys();

	UFUNCTION()
	void DecrementNumberOfEnemys();

	UFUNCTION()
	FORCEINLINE uint8 GetNumberOfFoods() const { return NumberOfFoods; };

	UFUNCTION()
	FORCEINLINE uint8 GetNumberOfEnemys() const { return NumberOfEnemys; };
};
