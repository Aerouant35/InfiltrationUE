// Fill out your copyright notice in the Description page of Project Settings.


#include "BTInteractFood.h"

EBTNodeResult::Type UBTInteractFood::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	if(AICon)
	{
		// Dépose la nourriture si l'IA en possède et si le spot n'en possède pas
		if(AICon->GetAICharacter()->GetHasFood()) // && !AICon->GetCurrentSpot()->HasAFood
			{
			//BlackboardComp = AICon->GetBlackboardComp();

			AICon->Interact();
		
			return EBTNodeResult::Succeeded;
			}
	}

	return EBTNodeResult::Failed;
}