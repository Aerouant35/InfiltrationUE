// Copyright Epic Games, Inc. All Rights Reserved.


#include "InfiltrationGameModeBase.h"
#include "EngineUtils.h"
#include "InfiltrationGameState.h"
#include "Characters/AI/AIGoblin.h"

AInfiltrationGameModeBase::AInfiltrationGameModeBase()
{
	DefaultPawnClass = ACharactKnight::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}

void AInfiltrationGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	Player = Cast<ACharactKnight>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	//check(!(FoodSpots.Num() < 1));
	if(FoodSpots.Num() < 1) return;
	GenerateStartFood();
}

void AInfiltrationGameModeBase::GenerateStartFood()
{
	const unsigned RandomNumSpot = FMath::RandRange(0, FoodSpots.Num() - 1);

	UE_LOG(LogTemp, Warning, TEXT("Food spot : %d"), RandomNumSpot);
	
		GetWorld()->SpawnActor<AFood>(FoodClass, FoodSpots[RandomNumSpot]->GetActorLocation(), FoodSpots[RandomNumSpot]->GetActorRotation());
		// Incremente la food au state
		Cast<AInfiltrationGameState>(GetWorld()->GetGameState())->IncrementNumberOfFoods();
}

#pragma region PublicMethod
void AInfiltrationGameModeBase::IncrementFood()
{
	CurrentFoodScore += 1;

	check(GameHUD != nullptr);
	GameHUD->UpdateProgressBarPercent(CurrentFoodScore);
	
	if (CurrentFoodScore >= NbFoodWin) Victory();
}

void AInfiltrationGameModeBase::Defeat() const
{
	check(!(GameHUD == nullptr || Player == nullptr || EnemySpawner == nullptr));

	// Show defeat widget
	GameHUD->ShowDefeatScreen();

	// Player : Lost
	Player->HasLost();
	
	// AI : Won
	for(AAIGoblin* AICharacter : EnemySpawner->GetSpawnedEnemy())
	{
		check(!(AICharacter == nullptr))
		
		AICharacter->HasWon();
	}
	EnemySpawner->StopSpawner();
}

void AInfiltrationGameModeBase::Victory() const
{
	check(!(GameHUD == nullptr || Player == nullptr || EnemySpawner == nullptr));
	
	// Show Victory widget
	GameHUD->ShowVictoryScreen();
	
	// Player : Won
	Player->HasWon();
	
	// AI : Lose
	for(AAIGoblin* AICharacter : EnemySpawner->GetSpawnedEnemy())
	{
		check(!(AICharacter == nullptr))

		AICharacter->HasLost();
	}
	EnemySpawner->StopSpawner();
}
#pragma endregion 
