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

	for (TActorIterator<AFoodSpot> FoodSpotItr(GetWorld()); FoodSpotItr; ++FoodSpotItr)
	{
		AFoodSpot* FoodSpot = *FoodSpotItr;
		FoodSpots.Add(FoodSpot);
	}

	if (FoodSpots.Num() < 1) return;
	GenerateStartFood();
}

void AInfiltrationGameModeBase::GenerateStartFood()
{
	const unsigned RandomNumSpot = FMath::RandRange(0, FoodSpots.Num() - 1);

	UE_LOG(LogTemp, Warning, TEXT("Food spot : %d"), RandomNumSpot);
	
	GetWorld()->SpawnActor<AFood>(FoodClass, FoodSpots[RandomNumSpot]->GetActorLocation(), FoodSpots[RandomNumSpot]->GetActorRotation());
}

void AInfiltrationGameModeBase::Victory()
{
	Cast<AGameHUD>(HUDClass)->ShowVictoryScreen();
}

void AInfiltrationGameModeBase::Defeat()
{
	Cast<AGameHUD>(HUDClass)->ShowDefeatScreen();
}

void AInfiltrationGameModeBase::PlayerTouched()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		AGameHUD* GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());
		if(GameHUD)
		{
			GameHUD->ShowDefeatScreen();

			// Player : Lost
			APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetPawn());
			if(Player)
			{
				Player->HasLost();
			}
			
			// AI : Won
			if(EnemySpawner)
			{
				for(AAICharacter* AICharacter : EnemySpawner->GetSpawnedEnemy())
				{
					AICharacter->HasWon();
				}
				EnemySpawner->StopSpawner();
			}
		}
	}
}

void AInfiltrationGameModeBase::IncrementReturnedFood()
{
	CurrentScore += 1;
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		AGameHUD* GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());
		if(GameHUD)
		{
			GameHUD->UpdateProgressBarPercent(CurrentScore);
			
			if(CurrentScore == NbFoodWin)
			{
				GameHUD->ShowVictoryScreen();
				
				// Player : Won
				APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetPawn());
				if(Player)
				{
					Player->HasWon();
				}
				
				// AI : Lose
				if(EnemySpawner)
				{
					for(AAICharacter* AICharacter : EnemySpawner->GetSpawnedEnemy())
					{
						if(AICharacter != nullptr)
						{
							AICharacter->HasLost();
						}
					}
					EnemySpawner->StopSpawner();
				}
			}
		}
	}
}

void AInfiltrationGameModeBase::RegisterSpawner(AEnemySpawner* Spawner)
{
	EnemySpawner = Spawner;
}
