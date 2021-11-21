// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIGoblin.h"
#include "FoodSpot.h"
#include "Characters/Player/CharactKnight.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "AICGoblin.generated.h"

UCLASS()
class INFILTRATION_API AAICGoblin : public AAIController
{
	GENERATED_BODY()

	#pragma region Variables
	bool bHasAlreadyDetected;

	FTimerHandle UnusedHandle;

	UPROPERTY()
	float SightLength = 1000.f;

	UPROPERTY()
	float SightAngle = 135.f;

	/*AIChar*/
	UPROPERTY()
	AAIGoblin* AIChar;

	/*Foodspot storage*/
	UPROPERTY()
	TArray<AActor*> FoodSpots;

	/*Current destination*/
	UPROPERTY()
	AFoodSpot* CurrentFoodSpot;

	/*Enemyspot*/
	UPROPERTY()
	AActor* EnemySpot;

	UPROPERTY()
	AActor* ExitSpot;

	/*Behavior tree comp ref*/
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;

	/*Blackboard comp ref*/
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;
	
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* AIPerceptionComponent; 

	/*Blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;
	#pragma endregion 

public:
	AAICGoblin();

	#pragma region Accessor
	UFUNCTION()
	AAIGoblin* GetAICharacter() const { return AIChar; }

	FORCEINLINE TArray<AActor*> GetAvailableFoodSpots() const { return FoodSpots; }

	FORCEINLINE AFoodSpot* GetCurrentSpot() const { return CurrentFoodSpot; }
	
	FORCEINLINE AActor* GetEnemySpot() const { return EnemySpot; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	#pragma endregion

private:
	/*Blackboard Initialize and start behavior tree*/
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	#pragma region PrivateMethod
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimuli);

	UFUNCTION()
	void TimerKeepFoodLocation() const;

	UFUNCTION()
	FVector GetSupposedPlayerPosition(const ACharactKnight* Player) const;

	UFUNCTION()
	FVector GetClosestLocationInNavMesh(FVector Location) const;
	
	#pragma endregion 

public:
	#pragma region PublicMethod
	UFUNCTION()
	void Interact() const;

	UFUNCTION()
	void SetCurrentSpot(AFoodSpot* NewCurrentSpot);

	UFUNCTION()
	void SetDefaultBehaviourTree();

	UFUNCTION()
	void SetEnemySpot(AActor* NewEnemySpot);
	
	UFUNCTION()
	void SetFoodSpots(TArray<AActor*> NewFoodSpots);
	#pragma endregion 
};
