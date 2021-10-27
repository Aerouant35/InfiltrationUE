// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "AICharacter.h"
#include "EnemySpot.h"
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
	bHasAlreadyDetected = false;
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

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, AIChar->GetName());
		}

		// Les spots sont définie par le spawner

		//Start the behavior tree which corresponds to the specific character
		BehaviorComp->StartTree(*AIChar->DefaultBehaviorTree);
	}
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AMyAIController::OnTargetPerceptionUpdated);}

void AMyAIController::SetEnemySpot(AActor* NewEnemySpot)
{
	EnemySpot = NewEnemySpot;
	BlackboardComp->SetValueAsObject("ExitSpot", EnemySpot);
}

void AMyAIController::SetFoodSpots(TArray<AActor*> NewFoodSpots)
{
	FoodSpots = NewFoodSpots;
}

void AMyAIController::Interact()
{
	AIChar->Interact();
	BlackboardComp->SetValueAsBool("bIsCarrying", AIChar->GetHasFood());
}

AAICharacter* AMyAIController::GetAICharacter()
{
	return AIChar;
}

void AMyAIController::SetCurrentSpot(AFoodSpot* NewCurrentSpot)
{
	CurrentFoodSpot = NewCurrentSpot;
}

void AMyAIController::SetDefaultBehaviourTree()
{
	bHasAlreadyDetected = false;
	BehaviorComp->StopTree();
	BehaviorComp->StartTree(*AIChar->DefaultBehaviorTree);
}

void AMyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimuli)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(Actor);
	if(Player)
	{
		// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("See Player"));

		if(!bHasAlreadyDetected)
		{
			bHasAlreadyDetected = true;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMyAIController::TimerKeepFoodLocation, 3.0f, false);
			BlackboardComp->SetValueAsBool("bWasCarrying", AIChar->GetHasFood());
		}
		
		BlackboardComp->SetValueAsVector("PlayerLocation", Player->GetActorLocation());
		BlackboardComp->SetValueAsVector("SupposedPlayerLocation", GetSupposedPlayerPosition(Player));

		BehaviorComp->StopTree();
		BehaviorComp->StartTree(*AIChar->ChaseBehaviorTree);
	}
}

void AMyAIController::TimerKeepFoodLocation()
{
	BlackboardComp->SetValueAsVector("DroppedFoodLocation", AIChar->GetCarryFoodLocation());
}

FVector AMyAIController::GetSupposedPlayerPosition(APlayerCharacter* Player)
{
	FRotator Rotation = Player->GetActorRotation();
	FRotator Yaw = FRotator(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
	FVector SupposedPlayerLocation = Player->GetActorLocation() + Direction * 1000;

	// Avoid being outside of the playground
	if(SupposedPlayerLocation.X > 2500.f) { SupposedPlayerLocation.X = 2500.f; }
	if(SupposedPlayerLocation.X < -500.f) { SupposedPlayerLocation.X = -500.f; }
	if(SupposedPlayerLocation.Y > 3500.f) { SupposedPlayerLocation.Y = 3500.f; }
	if(SupposedPlayerLocation.Y < -500.f) { SupposedPlayerLocation.Y = -500.f; }

	return SupposedPlayerLocation;
}

