// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/GameplayStatics.h"

AMyAIController::AMyAIController()
{
	//Initialize BehaviorTreeComponent, BlackboardComponent and the corresponding key

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	LocationToGoKey = "LocationToGo";
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Get the possessed Character and check if it's my own AI Character
	AIChar = Cast<AAICharacter>(InPawn);

	if(AIChar)
	{
		//If the blackboard is valid initialize the blackboard for the corresponding behavior tree
		if(AIChar->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
		}

		//Populate the array of available FoodSpots
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFoodSpot::StaticClass(), FoodSpots);

		// Je passe par l'inspecteur de AIChar pour definir mes spots
		FoodSpots = AIChar->FoodSpots;

		EnemySpot = AIChar->EnemySpot;

		//Start the behavior tree which corresponds to the specific character
		BehaviorComp->StartTree(*AIChar->BehaviorTree);
	}
}

void AMyAIController::Interact()
{
	AIChar->Interact();
}