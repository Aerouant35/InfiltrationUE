// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AI/BTTask/BTTask_FoodSpotSelection.h"
#include "FoodSpot.h"
#include "Characters/AI/ExitEnemySpot.h"
#include "Characters/AI/AICGoblin.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FoodSpotSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AAICGoblin>(OwnerComp.GetAIOwner());

	//Get blackboard Comp. and Current Spot
	//Search for the next spot != current spot
	if(AICon)
	{
		BlackboardComp = AICon->GetBlackboardComp();
		if(!BlackboardComp) return EBTNodeResult::Failed;
		BlackboardLocation = BlackboardComp->GetValueAsObject("LocationToGo");
		AAIGoblin* AIGoblin = AICon->GetAICharacter();
		if(!AIGoblin) return EBTNodeResult::Failed;
		if(BlackboardLocation == nullptr || AIGoblin->GetHasFood())
		{
			GoToFoodSpot();
		}
		else if(AIGoblin->GetPatrolState())
		{
			GoToFoodSpot();
			AIGoblin->DecrementNumberOfPatrols();
		}
		else
		{
			GoToEnemySpot();
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_FoodSpotSelection::GoToFoodSpot()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("FoodSpotLocation"));

	AFoodSpot* CurrentSpot = Cast<AFoodSpot>(BlackboardLocation);

	TArray<AActor*> AvailableFoodSpots = AICon->GetAvailableFoodSpots();
	
	AFoodSpot* NextSpot = nullptr;

	// Cette boucle est nécessaire si on enchaine des GoToFoodSpot à la suite
	// C'est à dire quand tout les spots de nourriture sont remplis
	do
	{
		// Random index of FoodSpot
		int32 RandomIndex = FMath::RandRange(0, AvailableFoodSpots.Num()-1);
		
		NextSpot = Cast<AFoodSpot>(AvailableFoodSpots[RandomIndex]);
	} while(CurrentSpot == NextSpot || NextSpot->HasAFood); // Choisit un spot qui n'a pas de la nourriture ou et qui ne correspond pas au précédent

	// /!\ Si le nombre de spot est égale ou inférieur au nombre de nourriture max d'un level alors le jeu peu crash /!\

	// Update next location in blackboard
	BlackboardComp->SetValueAsObject("LocationToGo", NextSpot);

	// Update AICon's destination
	AICon->SetCurrentSpot(NextSpot);
}

void UBTTask_FoodSpotSelection::GoToEnemySpot()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EnemySpotLocation"));

	AExitEnemySpot* NextSpot = Cast<AExitEnemySpot>(AICon->GetEnemySpot());

	BlackboardComp->SetValueAsObject("LocationToGo", NextSpot);
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, BlackboardComp->GetValueAsObject("LocationToGo")->GetName());
	
}


