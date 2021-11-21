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

AAIGoblin* AExitEnemySpot::DestroyEnemy() const
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

// Check if food is in collide area
void AExitEnemySpot::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef1 == nullptr)
	{
		NbEnemies++;
		EnemyRef1 = Cast<AAIGoblin>(OtherActor);
	}
	else if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef2 == nullptr)
	{
		NbEnemies++;
		EnemyRef2 = Cast<AAIGoblin>(OtherActor);
	}
	else if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef3 == nullptr)
	{
		NbEnemies++;
		EnemyRef3 = Cast<AAIGoblin>(OtherActor);
	}
}

void AExitEnemySpot::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef1 == OtherActor)
	{
		NbEnemies--;
		EnemyRef1 = nullptr;
	}
	else if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef2 == OtherActor)
	{
		NbEnemies--;
		EnemyRef2 = nullptr;
	}
	else if(OtherActor->IsA(AAIGoblin::StaticClass()) && EnemyRef3 == OtherActor)
	{
		NbEnemies--;
		EnemyRef3 = nullptr;
	}
}