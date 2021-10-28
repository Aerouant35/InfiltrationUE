// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Characters/AI/AICGoblin.h"
#include "BTTaskNode_DefaultTree.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UBTTaskNode_DefaultTree : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory) override;

	protected:

	//UPROPERTY(VisibleAnywhere)
	AAICGoblin* AICon;
	
};
