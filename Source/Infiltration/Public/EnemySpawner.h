// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIAnimations.h"
#include "AICharacter.h"
#include "EnemySpot.h"
#include "MyAIController.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class INFILTRATION_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Pour crée un delais d'appel de fonction
	FTimerHandle FirstTimerHandle;
	FTimerHandle SecondTimerHandle;
	
	FTimerHandle ThirdTimerHandle;
	FTimerHandle FourthTimerHandle;
	FTimerHandle FifthTimerHandle;

	int SpawnIndice = 0;

	UPROPERTY(VisibleAnywhere)
	TArray<AAICharacter*> SpawnedEnemy;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category="Spots")
	AEnemySpot* EnemySpot;

	UPROPERTY(EditAnywhere, Category="Spots")
	TArray<AActor*> FoodSpots;
	
	UPROPERTY(EditAnywhere, Category="ObjectToSpawn")
	TSubclassOf<AAICharacter> EnemyToSpawn;

	UPROPERTY(EditAnywhere, Category="ObjectToSpawn")
	TSubclassOf<AFood> FoodToSpawn;

	UPROPERTY(EditAnywhere, Category="Animation Enemy")
	TSubclassOf<UAnimInstance> BP_Anim;

	UFUNCTION()
		FORCEINLINE TArray<AAICharacter*> GetSpawnedEnemy() const { return SpawnedEnemy; }
		
	UFUNCTION()
	void SpawnEnemy();

	UFUNCTION()
	void GiveFood(AAICharacter* AICharRef);

	UFUNCTION()
	void RecreateAnEnemy();

	UFUNCTION()
	void StopSpawner();

	UFUNCTION()
	TArray<AAICharacter*> RemoveDestroyedEnemy();
};
