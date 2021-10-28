// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AI/BTTask/BTFoodSpotSelection.h"
#include "FoodSpot.h"
#include "Characters/AI/ExitEnemySpot.h"
#include "Characters/AI/AICGoblin.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTFoodSpotSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AAICGoblin>(OwnerComp.GetAIOwner());

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

	TArray<AActor*> AvailableFoodSpots = AICon->GetAvailableFoodSpots();

	//Random index of FoodSpot
	int32 RandomIndex;

	AFoodSpot* NextSpot = nullptr;
	
	// This loop is for give a foodSpot who doesn't have food and who is not like the previous one
	do
	{
		RandomIndex = FMath::RandRange(0, AvailableFoodSpots.Num()-1);
		
		NextSpot = Cast<AFoodSpot>(AvailableFoodSpots[RandomIndex]);
	} while(CurrentSpot == NextSpot || NextSpot->HasAFood);

	// /!\ If the numberOfFood can be equal or superior to the NumberOfFoodSpots, the game can crash /!\

	//Update next location in blackboard
	BlackboardComp->SetValueAsObject("LocationToGo", NextSpot);

	//Update AICon's destination
	AICon->SetCurrentSpot(NextSpot);
}

void UBTFoodSpotSelection::GoToEnemySpot()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EnemySpotLocation"));

	AExitEnemySpot* NextSpot = Cast<AExitEnemySpot>(AICon->GetEnemySpot());

	BlackboardComp->SetValueAsObject("LocationToGo", NextSpot);
}


