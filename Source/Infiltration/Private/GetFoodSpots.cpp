// Fill out your copyright notice in the Description page of Project Settings.


#include "GetFoodSpots.h"
#include "Infiltration/InfiltrationGameModeBase.h"

// Sets default values
AGetFoodSpots::AGetFoodSpots()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGetFoodSpots::BeginPlay()
{
	Super::BeginPlay();

	if (1 > FoodSpots.Num()) return;
	Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->SetFoodSpots(FoodSpots);
}

