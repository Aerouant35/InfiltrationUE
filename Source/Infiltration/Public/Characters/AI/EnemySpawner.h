// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGoblin.h"
#include "AIGoblin.h"
#include "AICGoblin.h"
#include "ExitEnemySpot.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class INFILTRATION_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

	#pragma region Variables
	// For delay spawn
	FTimerHandle FirstTimerHandle;
	FTimerHandle SecondTimerHandle;
	
	FTimerHandle ThirdTimerHandle;
	FTimerHandle FourthTimerHandle;
	FTimerHandle FifthTimerHandle;

	uint8 SpawnIndex = 0;

	UPROPERTY(EditAnywhere, Category="Spots")
	AExitEnemySpot* EnemySpot;

	UPROPERTY(EditAnywhere, Category="Spots")
	TArray<AActor*> FoodSpots;
	
	UPROPERTY(EditAnywhere, Category="ObjectToSpawn")
	TSubclassOf<AAIGoblin> EnemyToSpawn;

	UPROPERTY(EditAnywhere, Category="ObjectToSpawn")
	TSubclassOf<AFood> FoodToSpawn;

	UPROPERTY(EditAnywhere, Category="Animation Enemy")
	TSubclassOf<UAnimInstance> BP_Anim;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AAIGoblin*> SpawnedEnemy;
	#pragma endregion 

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	TArray<AAIGoblin*> GetSpawnedEnemy() const { return SpawnedEnemy; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	#pragma region ProtectedMethod
	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void GiveFood(AAIGoblin* AICharRef) const;

	UFUNCTION()
	void RecreateAnEnemy();

	UFUNCTION()
	TArray<AAIGoblin*> RemoveDestroyedEnemy();
	#pragma endregion 
	
public:
	UFUNCTION()
	void StopSpawner();

};
