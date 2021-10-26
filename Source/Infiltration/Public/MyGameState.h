// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpot.h"
#include "FoodSpot.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AMyGameState : public AGameState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Spots")
	AEnemySpot* EnemySpot;

	UPROPERTY(EditAnywhere, Category="Spots")
	TArray<AFoodSpot*> FoodSpots;

public:

	UFUNCTION()
	bool ThereIsAFreeFoodSpot();
};
