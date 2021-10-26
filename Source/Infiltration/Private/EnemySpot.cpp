// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpot.h"

#include "AICharacter.h"
#include "Food.h"

// Sets default values
AEnemySpot::AEnemySpot()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpot::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpot::OnComponentBeginOverlap);
}

// Called every frame
void AEnemySpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// Regarde si une nourriture est présent dans sa zone de collision
void AEnemySpot::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AAICharacter::StaticClass()))
	{
		HasAEnemy = true;
		EnemyRef = Cast<AAICharacter>(OtherActor);
	}
}

void AEnemySpot::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->IsA(AAICharacter::StaticClass()))
	{
		HasAEnemy = false;
		EnemyRef = nullptr;
	}
}