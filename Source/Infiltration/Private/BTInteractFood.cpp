// Fill out your copyright notice in the Description page of Project Settings.


#include "BTInteractFood.h"

EBTNodeResult::Type UBTInteractFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		//BlackboardComp = AICon->GetBlackboardComp();

		AICon->Interact();
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}