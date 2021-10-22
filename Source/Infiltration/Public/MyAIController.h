// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyAIController.generated.h"

UCLASS()
class INFILTRATION_API AMyAIController : public AAIController
{
	GENERATED_BODY()

	/*Behavior tree comp ref*/
	UBehaviorTreeComponent* BehaviorComp;

	/*Blackboard comp ref*/
	UBlackboardComponent* BlackboardComp;

	UBehaviorTreeComponent* BehaviorComp2;

	/*Blackboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;

	/*AIChar*/
	AAICharacter* AIChar;

	/*Foodspot storage*/
	TArray<AActor*> FoodSpots;

	/*Enemyspot*/
	AActor* EnemySpot;

	/*Blackboard Initialize and start behavior tree*/
	virtual void OnPossess(APawn* InPawn) override;

public:

	/*Constructor*/
	AMyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	FORCEINLINE TArray<AActor*> GetAvailableFoodSpots() const { return FoodSpots; }

	FORCEINLINE AActor* GetEnemySpot() const { return EnemySpot; }

	UFUNCTION()
	void Interact();
};
