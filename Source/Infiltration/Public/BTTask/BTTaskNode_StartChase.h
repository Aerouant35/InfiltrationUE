// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAIController.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_StartChase.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UBTTaskNode_StartChase : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) override;

	protected:

	//UPROPERTY(VisibleAnywhere)
	AMyAIController* AICon;		
};