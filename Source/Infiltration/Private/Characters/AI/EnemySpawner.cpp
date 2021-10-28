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

	Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->SetEnemySpawner(this);

    // Spawn de deux ennemis en début de partie
	SpawnEnemy();
	GetWorldTimerManager().SetTimer(FirstTimerHandle, this, &AEnemySpawner::SpawnEnemy, 2.f, false);

	// Spawn d'un troisième ennemi une minute plus tard
	GetWorldTimerManager().SetTimer(SecondTimerHandle, this, &AEnemySpawner::SpawnEnemy, 60.f, false);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// SpawnedEnemy = RemoveDestroyedEnemy();

	// Si l'ennemi reviens alors je le détruit pour en recrée un autre
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

		// Attribut les spots au controller
		Cast<AAICGoblin>(AICharRef->Controller)->SetEnemySpot(EnemySpot);
		Cast<AAICGoblin>(AICharRef->Controller)->SetFoodSpots(FoodSpots);

		// Attribut le BP_anim au personnage
		AICharRef->SetAnimation(BP_Anim);

		SpawnedEnemy.Add(AICharRef);

		// S'il y a moins de 5 nourriture dans le level alors j'en donne une à l'IA pour qu'il la dépose
		// Sinon il va patrouiller sans nourriture vers 2 spots avant de revenir
		int NumberOfFoods = Cast<AInfiltrationGameState>(GetWorld()->GetGameState())->GetNumberOfFoods();
		
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

		// Attribut la food a l'ennemi
		FoodRef->PickUp(AICharRef->GetHoldingComponent());
		AICharRef->SetHasFood(true, FoodRef);

		// Incremente la food au state
		Cast<AInfiltrationGameState>(GetWorld()->GetGameState())->IncrementFood();
	}
}

// Detruit l'enemy dans le spot enemy et en recrée un nouveau
void AEnemySpawner::RecreateAnEnemy()
{
	AAIGoblin* AICharToDestroy = EnemySpot->DestroyEnemy();
	if(AICharToDestroy)
	{
		SpawnedEnemy.Remove(AICharToDestroy);
	}
	
	// Spawn un ennemi entre 0 et 5s après
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

