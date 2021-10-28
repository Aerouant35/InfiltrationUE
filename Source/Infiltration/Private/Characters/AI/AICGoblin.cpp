// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/AICGoblin.h"
#include "Characters/AI/AIGoblin.h"
#include "NavigationSystem.h"
#include "Characters/Player/CharactKnight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAICGoblin::AAICGoblin()
{
	//Initialize BehaviorTreeComponent, BlackboardComponent and the corresponding key
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));


	UAISenseConfig_Sight* ConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SetPerceptionComponent(*AIPerceptionComponent);
	ConfigSight->SightRadius = SightLength;
	ConfigSight->LoseSightRadius = ConfigSight->SightRadius + 100.0f ;
	ConfigSight->PeripheralVisionAngleDegrees = SightAngle / 2.0f;
	ConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	ConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	ConfigSight->DetectionByAffiliation.bDetectFriendlies = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AIPerceptionComponent->SetDominantSense(ConfigSight->GetSenseImplementation());
	AIPerceptionComponent->ConfigureSense(*ConfigSight);
	
	LocationToGoKey = "LocationToGo";
	bHasAlreadyDetected = false;
}

void AAICGoblin::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Get the possessed Character and check if it's my own AI Character
	AIChar = Cast<AAIGoblin>(InPawn);
	check(AIChar != nullptr);
	
	//If the blackboard is valid initialize the blackboard for the corresponding behavior tree
	if(AIChar->GetDefaultBehaviourTree()->BlackboardAsset)
	{
		BlackboardComp->InitializeBlackboard(*(AIChar->GetDefaultBehaviourTree()->BlackboardAsset));
	}

	//Start the behavior tree which corresponds to the specific character
	BehaviorComp->StartTree(*AIChar->GetDefaultBehaviourTree());
}

void AAICGoblin::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAICGoblin::OnTargetPerceptionUpdated);
}

#pragma region PrivateMethod
void AAICGoblin::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimuli)
{
	ACharactKnight* Player = Cast<ACharactKnight>(Actor);
	if (Player == nullptr) return;
	
	if(!bHasAlreadyDetected)
	{
		bHasAlreadyDetected = true;
		if(AIChar->GetHasFood())
		{
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &AAICGoblin::TimerKeepFoodLocation, 1.0f, false);
		}
		BlackboardComp->SetValueAsBool("bWasCarrying", AIChar->GetHasFood());
	}
	
	BlackboardComp->SetValueAsVector("PlayerLocation", GetClosestLocationInNavMesh(Player->GetActorLocation()));
	BlackboardComp->SetValueAsVector("SupposedPlayerLocation", GetSupposedPlayerPosition(Player));

	BehaviorComp->StopTree();
	BehaviorComp->StartTree(*AIChar->GetChaseBehaviourTree());
}

void AAICGoblin::TimerKeepFoodLocation() const
{
	BlackboardComp->SetValueAsVector("DroppedFoodLocation", AIChar->GetDroppedFoodLocation());
}

FVector AAICGoblin::GetSupposedPlayerPosition(const ACharactKnight* Player) const 
{
	const FRotator Rotation = Player->GetActorRotation();
	const FRotator Yaw = FRotator(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
	const FVector SupposedPlayerLocation = Player->GetActorLocation() + Direction * 1000;

	// Avoid being outside of the playground
	return GetClosestLocationInNavMesh(SupposedPlayerLocation);
}

FVector AAICGoblin::GetClosestLocationInNavMesh(FVector Location) const
{
	FNavLocation NavLocation;
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	NavigationSystem->ProjectPointToNavigation(Location, NavLocation, FVector(1000.f, 1000.f, 100.f));
	return NavLocation.Location;
}
#pragma endregion 

#pragma region PublicMethod
void AAICGoblin::Interact() const
{
	AIChar->Interact();
	BlackboardComp->SetValueAsBool("bIsCarrying", AIChar->GetHasFood());
}

void AAICGoblin::SetCurrentSpot(AFoodSpot* NewCurrentSpot)
{
	CurrentFoodSpot = NewCurrentSpot;
}

void AAICGoblin::SetDefaultBehaviourTree()
{
	bHasAlreadyDetected = false;
	BehaviorComp->StopTree();
	BehaviorComp->StartTree(*AIChar->GetDefaultBehaviourTree());
}

void AAICGoblin::SetEnemySpot(AActor* NewEnemySpot)
{
	EnemySpot = NewEnemySpot;
	BlackboardComp->SetValueAsObject("ExitSpot", EnemySpot);
}

void AAICGoblin::SetFoodSpots(const TArray<AActor*> NewFoodSpots)
{
	FoodSpots = NewFoodSpots;
}
#pragma endregion 
