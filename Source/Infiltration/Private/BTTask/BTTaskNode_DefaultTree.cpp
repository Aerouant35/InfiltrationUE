// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask/BTTaskNode_DefaultTree.h"

EBTNodeResult::Type UBTTaskNode_DefaultTree::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	
	if(AICon)
	{
		AICon->SetDefaultBehaviourTree();
		
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}