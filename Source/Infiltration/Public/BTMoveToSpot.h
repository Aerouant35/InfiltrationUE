// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyAIController.h"
#include "BTMoveToSpot.generated.h"


UCLASS()
class INFILTRATION_API UBTMoveToSpot : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) override;

protected:
	
	//UPROPERTY(VisibleAnywhere)
	AMyAIController* AICon;

	//UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BlackboardComp;
};
