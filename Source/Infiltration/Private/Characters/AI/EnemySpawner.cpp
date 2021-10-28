// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/EnemySpawner.h"
#include "InfiltrationGameState.h"
#include "Infiltration/InfiltrationGameModeBase.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	AInfiltrationGameModeBase* GameModeBase = Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode());
	check(GameModeBase != nullptr);
	GameModeBase->SetEnemySpawner(this);

    // Spawn of two enemy in the start of the game
	SpawnEnemy();
	GetWorldTimerManager().SetTimer(FirstTimerHandle, this, &AEnemySpawner::SpawnEnemy, 2.f, false);

	// Spawn of the third enemy, one minute later
	GetWorldTimerManager().SetTimer(SecondTimerHandle, this, &AEnemySpawner::SpawnEnemy, 60.f, false);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If the enemy come back, I destroy him and create another one
	if(EnemySpot->GetNumberOfEnemys() > 0)
	{
		RecreateAnEnemy();
	}
}

void AEnemySpawner::SpawnEnemy()
{
	if(EnemyToSpawn)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = FRotator (0,0,0);
	
		AAIGoblin* AICharRef = GetWorld()->SpawnActor<AAIGoblin>(EnemyToSpawn, Location, Rotation);

		// Add the spots to the controller
		AAICGoblin* AICGobelin = Cast<AAICGoblin>(AICharRef->Controller);
		check(AICGobelin != nullptr);
		AICGobelin->SetEnemySpot(EnemySpot);
		AICGobelin->SetFoodSpots(FoodSpots);

		// Add the BP_anim to the player
		AICharRef->SetAnimation(BP_Anim);

		SpawnedEnemy.Add(AICharRef);

		// If there is less than 5 foods in the game, I give one to the AI
		// Else, the AI go to two spot without food before come back
		AInfiltrationGameState* GameState = Cast<AInfiltrationGameState>(GetWorld()->GetGameState());
		check(GameState != nullptr);
		int NumberOfFoods = GameState->GetNumberOfFoods();
		
		if(NumberOfFoods < 5)
		{
			GiveFood(AICharRef);
		}
		else
		{
			AICharRef->SetPatrolState(true, 2);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("spawn"));
	}
}

void AEnemySpawner::GiveFood(AAIGoblin* AICharRef)
{
	if(FoodToSpawn)
	{
		FVector Location = GetActorLocation();
		FRotator Rotation = FRotator (0,0,0);
	
		AFood* FoodRef = GetWorld()->SpawnActor<AFood>(FoodToSpawn, Location, Rotation);

		// Add food to enemy
		FoodRef->PickUp(AICharRef->GetHoldingComponent());
		AICharRef->SetHasFood(true, FoodRef);

		// Increments the number of foods in the GameState
		AInfiltrationGameState* GameState = Cast<AInfiltrationGameState>(GetWorld()->GetGameState());
		check(GameState != nullptr);
		GameState->IncrementNumberOfFoods();
	}
}

// Destroy enemy and create another one
void AEnemySpawner::RecreateAnEnemy()
{
	AAIGoblin* AICharToDestroy = EnemySpot->DestroyEnemy();
	
	if(AICharToDestroy)
	{
		SpawnedEnemy.Remove(AICharToDestroy);

		// If there is no enemy, spawn directly one other, if not, spawn between 0 and 5s one other
		AInfiltrationGameState* GameState = Cast<AInfiltrationGameState>(GetWorld()->GetGameState());
		check(GameState != nullptr);
		int NumberOfEnemys = GameState->GetNumberOfEnemys();
		if(NumberOfEnemys > 0)
		{
			switch (SpawnIndice)
			{
			case 0:
				GetWorldTimerManager().SetTimer(ThirdTimerHandle, this, &AEnemySpawner::SpawnEnemy, FMath::RandRange(0.f, 5.f), false);
				SpawnIndice++;
				break;

			case 1: GetWorldTimerManager().SetTimer(FourthTimerHandle, this, &AEnemySpawner::SpawnEnemy, FMath::RandRange(0.f, 5.f), false);
				SpawnIndice++;
				break;
		
			case 2: GetWorldTimerManager().SetTimer(FifthTimerHandle, this, &AEnemySpawner::SpawnEnemy, FMath::RandRange(0.f, 5.f), false);
				SpawnIndice = 0;
				break;
			}
		}
		else
		{
			SpawnEnemy();
		}
	}
}

void AEnemySpawner::StopSpawner()
{
	// Stop all the timer that can spawn enemy
	FirstTimerHandle.Invalidate();
	SecondTimerHandle.Invalidate();
	ThirdTimerHandle.Invalidate();
	FourthTimerHandle.Invalidate();
	FifthTimerHandle.Invalidate();
}

TArray<AAIGoblin*> AEnemySpawner::RemoveDestroyedEnemy()
{
	TArray<AAIGoblin*> NewArray;
	for (int32 i = 0; i < SpawnedEnemy.Num(); ++i)
	{
		if (SpawnedEnemy[i] != nullptr)
		{
			NewArray.Add(SpawnedEnemy[i]);
		}
	}
	return NewArray;
}

