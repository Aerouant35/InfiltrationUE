// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICharacter.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyAIController.generated.h"

UCLASS()
class INFILTRATION_API AMyAIController : public AAIController
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
	AAICharacter* AIChar;

	/*Foodspot storage*/
	TArray<AActor*> FoodSpots;

	/*Enemyspot*/
	AActor* EnemySpot;

	AActor* ExitSpot;

	/*Blackboard Initialize and start behavior tree*/
	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimuli);

	UFUNCTION()
		void TimerKeepFoodLocation();

	FVector GetSupposedPlayerPosition(APlayerCharacter* Player);


public:

	/*Constructor*/
	AMyAIController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	FORCEINLINE TArray<AActor*> GetAvailableFoodSpots() const { return FoodSpots; }

	FORCEINLINE AActor* GetEnemySpot() const { return EnemySpot; }

	UFUNCTION()
		void Interact();

	UFUNCTION()
		AAICharacter* GetAICharacter();

	UFUNCTION()
		void SetDefaultBehaviourTree();
};
