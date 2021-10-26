// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


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

    // Spawn de deux ennemis en début de partie
	SpawnEnemy();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::SpawnEnemy, 2.f, false);

	// Spawn d'un troisième ennemi une minute plus tard
	GetWorldTimerManager().SetTimer(SecondTimerHandle, this, &AEnemySpawner::SpawnEnemy, 60.f, false);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Si l'ennemi reviens alors je le détruit pour en recrée un autre
	if(EnemySpot->HasAEnemy)
	{
		RecreateAnEnemy();
	}
}

void AEnemySpawner::SpawnEnemy()
{
	if(EnemyToSpawn)
	{
		FVector Location = FVector(EnemySpot->GetActorLocation().X, EnemySpot->GetActorLocation().Y + 300, EnemySpot->GetActorLocation().Z);
		FRotator Rotation = FRotator (0,0,0);
	
		AAICharacter* AICharRef = GetWorld()->SpawnActor<AAICharacter>(EnemyToSpawn, Location, Rotation);

		// Attribut les spots au controller
		Cast<AMyAIController>(AICharRef->Controller)->SetEnemySpot(EnemySpot);
		Cast<AMyAIController>(AICharRef->Controller)->SetFoodSpots(FoodSpots);

		// Attribut le BP_anim au personnage
		AICharRef->SetAnimation(BP_Anim);

		// S'il y a moins de 5 nourriture dans le level alors j'en donne une à l'IA pour qu'il la dépose
		// Sinon il va patrouiller sans nourriture vers 2 spots avant de revenir
		if(true)
		{
			GiveFood(AICharRef);
		}
		else
		{
			AICharRef->SetPatrolState(true, 2);
		}

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("spawn"));
	}
}

void AEnemySpawner::GiveFood(AAICharacter* AICharRef)
{
	if(FoodToSpawn)
	{
		FVector Location = FVector(EnemySpot->GetActorLocation().X, EnemySpot->GetActorLocation().Y, EnemySpot->GetActorLocation().Z + 100);
		FRotator Rotation = FRotator (0,0,0);
	
		AFood* FoodRef = GetWorld()->SpawnActor<AFood>(FoodToSpawn, Location, Rotation);

		// Attribut la food a l'ennemi
		FoodRef->PickUp(AICharRef->GetHoldingComponent());
		AICharRef->SetHasFood(true, FoodRef);
	}
}

// Detruit l'enemy dans le spot enemy et en recrée un nouveau
void AEnemySpawner::RecreateAnEnemy()
{
	EnemySpot->EnemyRef->Destroy();
	EnemySpot->HasAEnemy = false;

	// /!\ Si plusieurs ennemis reviennent en même temps dans la salle, cela n'en fera spawn qu'un seul /!\
	
	// Spawn un ennemi entre 0 et 5s après
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::SpawnEnemy, FMath::RandRange(0.f, 5.f), false);
}

