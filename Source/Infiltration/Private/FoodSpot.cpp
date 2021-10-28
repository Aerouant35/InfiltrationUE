// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodSpot.h"
#include "Food.h"

// Sets default values
AFoodSpot::AFoodSpot()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFoodSpot::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFoodSpot::OnComponentBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AFoodSpot::OnComponentEndOverlap);
}

// Called every frame
void AFoodSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Look if food is already inside his overlap area
void AFoodSpot::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AFood::StaticClass()))
	{
		HasAFood = true;
		NumberOfFoods++;

		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("ADD"));
	}
}

void AFoodSpot::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->IsA(AFood::StaticClass()))
	{
		HasAFood = false;
		NumberOfFoods--;

		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("REMOVE"));
	}
}