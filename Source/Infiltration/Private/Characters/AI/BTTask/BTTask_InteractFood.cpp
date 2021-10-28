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

		// Dépose la nourriture si l'IA en possède et si le spot n'en possède pas
		// Pour une raison qui m'échappe, les foodSpot Overlap deux fois pour chaque fruit
		// Donc une valeur de 2 pour NumberOfFoods correspond en réalité à un seul fruit
		if(AIGoblin->GetHasFood() || AIGoblin->GetHasDropFood() && FoodSpot->GetNumberOfFoods() < 3)
		{
			AICon->Interact();
		
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}