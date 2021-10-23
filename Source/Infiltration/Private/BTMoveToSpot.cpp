// Fill out your copyright notice in the Description page of Project Settings.


#include "BTMoveToSpot.h"

EBTNodeResult::Type UBTMoveToSpot::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		//BlackboardComp = AICon->GetBlackboardComp();

		//
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}