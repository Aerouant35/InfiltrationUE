// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/ExitEnemySpot.h"
#include "Characters/AI/AIGoblin.h"
#include "Food.h"

// Sets default values
AExitEnemySpot::AExitEnemySpot()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AExitEnemySpot::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AExitEnemySpot::OnComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AExitEnemySpot::OnComponentEndOverlap);
}

// Called every frame
void AExitEnemySpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AAIGoblin* AExitEnemySpot::DestroyEnemy()
{
	AAIGoblin* EnemyRef = nullptr;
	if(EnemyRef1 != nullptr)
	{
		EnemyRef = EnemyRef1;
		EnemyRef1->Destroy();
	}
	else if(EnemyRef2 != nullptr)
	{
		EnemyRef = EnemyRef2;
		EnemyRef2->Destroy();
	}
	else if(EnemyRef3 != nullptr)
	{
		EnemyRef = EnemyRef3;
		EnemyRef3->Destroy();
	}
	return EnemyRef;
}

/// Regarde si une nourriture est présent dans sa zone de collision
void AExitEnemySpot::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef1 == nullptr)
	{
		NumberOfEnemys++;
		EnemyRef1 = Cast<AAIGoblin>(OtherActor);
	}
	else if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef2 == nullptr)
	{
		NumberOfEnemys++;
		EnemyRef2 = Cast<AAIGoblin>(OtherActor);
	}
	else if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef3 == nullptr)
	{
		NumberOfEnemys++;
		EnemyRef3 = Cast<AAIGoblin>(OtherActor);
	}
}

void AExitEnemySpot::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef1 == OtherActor)
	{
		NumberOfEnemys--;
		EnemyRef1 = nullptr;
	}
	else if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef2 == OtherActor)
	{
		NumberOfEnemys--;
		EnemyRef2 = nullptr;
	}
	else if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef3 == OtherActor)
	{
		NumberOfEnemys--;
		EnemyRef3 = nullptr;
	}
}