// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawner.h"
#include "Food.h"
#include "FoodSpot.h"
#include "GameFramework/GameModeBase.h"
#include "UI/Level/GameHUD.h"
#include "InfiltrationGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AInfiltrationGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Food")
	TSubclassOf<AFood> FoodClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Food")
	unsigned NbFoodWin = 5;

	UPROPERTY(VisibleAnywhere, Category="Food")
	TArray<AFoodSpot*> FoodSpots;

	UPROPERTY(VisibleAnywhere)
	float CurrentScore;

	AEnemySpawner* EnemySpawner;

public:
	AInfiltrationGameModeBase();

	unsigned GetNbFoodWin() const
	{
		return NbFoodWin;
	}

	float GetCurrentNbFood() const
	{
		return CurrentScore;
	}

	TArray<AFoodSpot*> GetFoodSpots() const
	{
		return FoodSpots;
	}

	void SetFoodSpots(const TArray<AFoodSpot*> NewFoodSpots)
	{
		FoodSpots = NewFoodSpots;
	}
	
	virtual void BeginPlay() override;

	void GenerateStartFood();
	
	void Victory();

	void Defeat();

	UFUNCTION()
		void PlayerTouched();

	UFUNCTION()
		void IncrementReturnedFood();
	UFUNCTION()
		void RegisterSpawner(AEnemySpawner* Spawner);
	
};
