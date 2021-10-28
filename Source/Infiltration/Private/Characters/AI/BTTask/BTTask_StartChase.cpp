// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTTask/BTTask_StartChase.h"

EBTNodeResult::Type UBTTask_StartChase::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AAICGoblin>(OwnerComp.GetAIOwner());
	
	if(AICon)
	{
		AAIGoblin* AICharacter =  AICon->GetAICharacter();
		// If AI is carrying : Drop the food
		if(AICharacter->GetHasFood())
		{
			AICharacter->SetHasFood(false, nullptr);
		}
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}