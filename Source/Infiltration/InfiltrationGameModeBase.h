// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI/EnemySpawner.h"
#include "Food.h"
#include "FoodSpot.h"
#include "Characters/Player/CharactKnight.h"
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

	#pragma region EditorVariables
	UPROPERTY(EditDefaultsOnly, Category="Food")
	TSubclassOf<AFood> FoodClass;

	UPROPERTY(VisibleAnywhere, Category="Food")
	TArray<AFoodSpot*> FoodSpots;

	UPROPERTY(EditDefaultsOnly, Category="Food")
	uint8 NbFoodWin = 5;

	UPROPERTY(VisibleAnywhere)
	uint8 CurrentFoodScore;
	#pragma endregion

	#pragma region StoragesVariables
	UPROPERTY()
	AEnemySpawner* EnemySpawner;

	UPROPERTY()
	AGameHUD* GameHUD;

	UPROPERTY()
	ACharactKnight* Player;
	#pragma endregion 

public:
	AInfiltrationGameModeBase();

	#pragma region Accessor
	TArray<AFoodSpot*> GetFoodSpots() const	{ return FoodSpots; }

	void SetFoodSpots(const TArray<AFoodSpot*> &NewFoodSpots) { FoodSpots = NewFoodSpots; }

	uint8 GetNbFoodWin() const { return NbFoodWin; }

	uint8 GetCurrentNbFood() const { return CurrentFoodScore; }

	UFUNCTION()
	void SetEnemySpawner(AEnemySpawner* Spawner) { EnemySpawner = Spawner; }
	#pragma endregion 
private:
	
	virtual void BeginPlay() override;

	void GenerateStartFood();

public:
	#pragma region PublicMethod
	void IncrementFood();
	
	UFUNCTION()
	void Defeat() const;

	UFUNCTION()
	void Victory() const;
	#pragma endregion 
};
