// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTTask/BTInteractFood.h"

EBTNodeResult::Type UBTInteractFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AAICGoblin>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		// Drop food if AI have one and if the spot doesn't
		// I don't understand why the BP_Food overlap two time so if the value use is 3 it's because 2 correspond to one food
		if(AICon->GetAICharacter()->GetHasFood() || AICon->GetAICharacter()->GetHasDropFood() && AICon->GetCurrentSpot()->GetNumberOfFoods() < 3)
			{
			AICon->Interact();
		
			return EBTNodeResult::Succeeded;
			}
	}

	return EBTNodeResult::Failed;
}