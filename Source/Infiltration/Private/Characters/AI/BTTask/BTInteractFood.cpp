// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTTask/BTInteractFood.h"

EBTNodeResult::Type UBTInteractFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AAICGoblin>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		// Dépose la nourriture si l'IA en possède et si le spot n'en possède pas
		// Pour une raison qui m'échappe, les foodSpot Overlap deux fois pour chaque fruit
		// Donc une valeur de 2 pour NumberOfFoods correspond en réalité à un seul fruit
		if(AICon->GetAICharacter()->GetHasFood() || AICon->GetAICharacter()->GetHasDropFood() && AICon->GetCurrentSpot()->GetNumberOfFoods() < 3)
			{
			//BlackboardComp = AICon->GetBlackboardComp();

			AICon->Interact();
		
			return EBTNodeResult::Succeeded;
			}
	}

	return EBTNodeResult::Failed;
}