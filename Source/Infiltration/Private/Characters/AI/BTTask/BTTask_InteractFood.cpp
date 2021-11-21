// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTTask/BTTask_InteractFood.h"

EBTNodeResult::Type UBTTask_InteractFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AAICGoblin>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		// Check pointers
		AAIGoblin* AIGoblin = AICon->GetAICharacter();
		if(!AIGoblin) return EBTNodeResult::Failed;
		AFoodSpot* FoodSpot = AICon->GetCurrentSpot();
		if(!FoodSpot) return EBTNodeResult::Failed;

		// Drop food if AI have one and if the spot doesn't
		// I don't understand why the BP_Food overlap two time so if the value use is 3 it's because 2 correspond to one food
		if((AIGoblin->GetHasFood() && FoodSpot->GetNumberOfFoods() < 3) || AIGoblin->GetHasDropFood())
		{
			AICon->Interact();
		
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
