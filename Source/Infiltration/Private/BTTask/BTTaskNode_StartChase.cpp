// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask/BTTaskNode_StartChase.h"

EBTNodeResult::Type UBTTaskNode_StartChase::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	
	if(AICon)
	{
		AAICharacter* AICharacter =  AICon->GetAICharacter();
		// If AI is carrying : Drop the food
		if(AICharacter->GetHasFood())
		{
			AICharacter->SetHasFood(false, nullptr);
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}