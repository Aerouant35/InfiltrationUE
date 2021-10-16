// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodSpot.h"
#include "EnemySpot.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BTFoodSpotSelection.h"

EBTNodeResult::Type UBTFoodSpotSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8* NodeMemory)
{
	AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());

	//Get blackboard Comp. and Current Spot
	//Search for the next spot != current spot
	if(AICon)
	{
		BlackboardComp = AICon->GetBlackboardComp();
		BlackboardLocation = BlackboardComp->GetValueAsObject("LocationToGo");

		if(BlackboardLocation == nullptr)
		{
			Begin();
		}
		else if(BlackboardLocation->IsA(AEnemySpot::StaticClass()))
		{
			GoToFoodSpot();
		}
		else if(BlackboardLocation->IsA(AFoodSpot::StaticClass()))
		{
			GoToEnemySpot();
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

// Methode appeler lors de la premiere selection de location
void UBTFoodSpotSelection::Begin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Start"));

	GoToEnemySpot();
}

// Methode appeler si l'on se trouve au spot Enemy
void UBTFoodSpotSelection::GoToFoodSpot()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("FoodSpotLocation"));

	AFoodSpot* CurrentSpot = Cast<AFoodSpot>(BlackboardLocation);

	TArray<AActor*> AvailableFoodSpots = AICon->GetAvailableFoodSpots();

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
	} while(CurrentSpot == NextSpot);

	//Update next location in blackboard
	BlackboardComp->SetValueAsObject("LocationToGo", NextSpot);
}

// Methode appeler si l'on se trouve au spot Food
void UBTFoodSpotSelection::GoToEnemySpot()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("EnemySpotLocation"));

	AEnemySpot* NextSpot = Cast<AEnemySpot>(AICon->GetEnemySpot());

	BlackboardComp->SetValueAsObject("LocationToGo", NextSpot);
}

