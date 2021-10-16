// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyAIController.h"
#include "BTFoodSpotSelection.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UBTFoodSpotSelection : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) override;

protected:
	
	//UPROPERTY(VisibleAnywhere)
	AMyAIController* AICon;

	//UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BlackboardComp;

	//UPROPERTY(VisibleAnywhere)
	UObject* BlackboardLocation;

public:

	UFUNCTION()
	void Begin();

	UFUNCTION()
	void GoToFoodSpot();

	UFUNCTION()
	void GoToEnemySpot();
};
