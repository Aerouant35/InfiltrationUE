// Fill out your copyright notice in the Description page of Project Settings.
#include "BTFoodSpotSelection.h"

#include "FoodSpot.h"
#include "EnemySpot.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"



EBTNodeResult::Type UBTFoodSpotSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	//Get blackboard Comp. and Current Spot
	//Search for the next spot != current spot
	if(AICon)
	{
		BlackboardComp = AICon->GetBlackboardComp();
		BlackboardLocation = BlackboardComp->GetValueAsObject("LocationToGo");

		if(BlackboardLocation == nullptr || AICon->GetAICharacter()->GetHasFood())
		{
			GoToFoodSpot();
		}
		else if(AICon->GetAICharacter()->GetPatrolState())
		{
			GoToFoodSpot();
			AICon->GetAICharacter()->DecrementNumberOfPatrols();
		}
		else
		{
			GoToEnemySpot();
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

void UBTFoodSpotSelection::GoToFoodSpot()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("FoodSpotLocation"));

	AFoodSpot* CurrentSpot = Cast<AFoodSpot>(BlackboardLocation);

	TArray<AFoodSpot*> AvailableFoodSpots = AICon->GetAvailableFoodSpots();

	//Random index of FoodSpot
	int32 RandomIndex;

	AFoodSpot* NextSpot = nullptr;

	// Cette boucle est nécessaire si on enchaine des GoToFoodSpot à la suite
	// C'est à dire quand tout les spots de nourriture sont remplis
	do
	{
		RandomIndex = FMath::RandRange(0, AvailableFoodSpots.Num()-1);

		//Cast because Array contains AActor*
		NextSpot = Cast<AFoodSpot>(AvailableFoodSpots[RandomIndex]);
	} while(CurrentSpot == NextSpot || NextSpot->HasAFood); // Choisit un spot qui n'a pas de la nourriture ou et qui ne correspond pas au précédent

	// /!\ Si le nombre de spot est égale ou inférieur au nombre de nourriture max d'un level alors le jeu peu crash /!\

	//Update next location in blackboard
	BlackboardComp->SetValueAsObject("LocationToGo", NextSpot);

	//Update AICon's destination
	AICon->SetCurrentSpot(NextSpot);
}

void UBTFoodSpotSelection::GoToEnemySpot()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EnemySpotLocation"));

	AEnemySpot* NextSpot = Cast<AEnemySpot>(AICon->GetEnemySpot());

	BlackboardComp->SetValueAsObject("LocationToGo", NextSpot);
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, BlackboardComp->GetValueAsObject("LocationToGo")->GetName());
	
}


