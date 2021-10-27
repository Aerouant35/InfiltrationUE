// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpot.h"
#include "FoodSpot.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Spots")
	AEnemySpot* EnemySpot;

	UPROPERTY(EditAnywhere, Category="Spots")
	TArray<AFoodSpot*> FoodSpots;

public:

	AMyGameState();

	UFUNCTION()
	bool ThereIsAFreeFoodSpot();
};
