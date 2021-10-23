// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "AICharacter.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMyAIController::AMyAIController()
{
	//Initialize BehaviorTreeComponent, BlackboardComponent and the corresponding key

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));


	UAISenseConfig_Sight* ConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SetPerceptionComponent(*AIPerceptionComponent);
	ConfigSight->SightRadius = 1000.0f;
	ConfigSight->LoseSightRadius = ConfigSight->SightRadius + 100.0f ;
	ConfigSight->PeripheralVisionAngleDegrees = 135.0f / 2.0f;
	ConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	ConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	ConfigSight->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AIPerceptionComponent->SetDominantSense(ConfigSight->GetSenseImplementation());
	AIPerceptionComponent->ConfigureSense(*ConfigSight);
	
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
		if(AIChar->DefaultBehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIChar->DefaultBehaviorTree->BlackboardAsset));
		}

		//Populate the array of available FoodSpots
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFoodSpot::StaticClass(), FoodSpots);

		// Je passe par l'inspecteur de AIChar pour definir mes spots
		FoodSpots = AIChar->FoodSpots;
		EnemySpot = AIChar->EnemySpot;

		//Start the behavior tree which corresponds to the specific character
		BehaviorComp->StartTree(*AIChar->DefaultBehaviorTree);
	}
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetPerceptionUpdated);
}

void AMyAIController::Interact()
{
	AIChar->Interact();
}

AAICharacter* AMyAIController::GetAICharacter()
{
	return AIChar;
}

void AMyAIController::SetDefaultBehaviourTree()
{
	BehaviorComp->StopTree();
	BehaviorComp->StartTree(*AIChar->DefaultBehaviorTree);
}

void AMyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimuli)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(Actor);
	if(Player)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("See Player"));
		
		BlackboardComp->SetValueAsVector("PlayerLocation", Player->GetActorLocation());
		BlackboardComp->SetValueAsRotator("PlayerDirection", Player->GetActorRotation());
		
		FRotator Rotation = Player->GetActorRotation();
		FRotator Yaw = FRotator(0, Rotation.Yaw, 0);
		FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		// WARNING : This Location can be outside the GameZone or the NavMesh
		FVector SupposedPlayerLocation = Player->GetActorLocation() + Direction * 1000;
		BlackboardComp->SetValueAsVector("SupposedPlayerLocation", SupposedPlayerLocation);

		BehaviorComp->StopTree();
		BehaviorComp->StartTree(*AIChar->ChaseBehaviorTree);
	}
}
