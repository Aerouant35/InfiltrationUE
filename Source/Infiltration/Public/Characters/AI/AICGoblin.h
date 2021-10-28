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

	/*Behavior tree comp ref*/
	UBehaviorTreeComponent* BehaviorComp;

	/*Blackboard comp ref*/
	UBlackboardComponent* BlackboardComp;

	bool bHasAlreadyDetected;

	FTimerHandle UnusedHandle;

	UPROPERTY(EditAnywhere)
		UAIPerceptionComponent* AIPerceptionComponent; 

	/*Blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;

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

	UPROPERTY()
	float SightLength = 1000.f;

	UPROPERTY()
	float SightAngle = 135.f;
	
	/*Blackboard Initialize and start behavior tree*/
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimuli);

	UFUNCTION()
		void TimerKeepFoodLocation() const;

	UFUNCTION()
	FVector GetSupposedPlayerPosition(const ACharactKnight* Player) const;


public:

	/*Constructor*/
	AAICGoblin();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	FORCEINLINE TArray<AActor*> GetAvailableFoodSpots() const { return FoodSpots; }

	FORCEINLINE AActor* GetEnemySpot() const { return EnemySpot; }

	FORCEINLINE AFoodSpot* GetCurrentSpot() const { return CurrentFoodSpot; }

	UFUNCTION()
		void Interact() const;

	UFUNCTION()
	AAIGoblin* GetAICharacter() const { return AIChar; }

	UFUNCTION()
		void SetCurrentSpot(AFoodSpot* NewCurrentSpot);

	UFUNCTION()
		void SetDefaultBehaviourTree();

	UFUNCTION()
		void SetEnemySpot(AActor* NewEnemySpot);
	
	UFUNCTION()
		void SetFoodSpots(TArray<AActor*> NewFoodSpots);
};
