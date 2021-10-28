// Copyright Epic Games, Inc. All Rights Reserved.


#include "InfiltrationGameModeBase.h"
#include "EngineUtils.h"
#include "PlayerCharacter.h"


AInfiltrationGameModeBase::AInfiltrationGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	HUDClass = AGameHUD::StaticClass();
}

void AInfiltrationGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	check(!(FoodSpots.Num() < 1));
	GenerateStartFood();
}

void AInfiltrationGameModeBase::GenerateStartFood()
{
	const unsigned RandomNumSpot = FMath::RandRange(0, FoodSpots.Num() - 1);

	UE_LOG(LogTemp, Warning, TEXT("Food spot : %d"), RandomNumSpot);
	
	GetWorld()->SpawnActor<AFood>(FoodClass, FoodSpots[RandomNumSpot]->GetActorLocation(), FoodSpots[RandomNumSpot]->GetActorRotation());
}

#pragma region PublicMethod
void AInfiltrationGameModeBase::IncrementFood()
{
	CurrentFoodScore += 1;

	check(!(GameHUD == nullptr));
	if (GameHUD == nullptr) return;
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
	for(AAICharacter* AICharacter : EnemySpawner->GetSpawnedEnemy())
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
	for(AAICharacter* AICharacter : EnemySpawner->GetSpawnedEnemy())
	{
		check(!(AICharacter == nullptr))

		AICharacter->HasLost();
	}
	EnemySpawner->StopSpawner();
}
#pragma endregion 
