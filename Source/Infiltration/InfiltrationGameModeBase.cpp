// Copyright Epic Games, Inc. All Rights Reserved.


#include "InfiltrationGameModeBase.h"

#include "EngineUtils.h"
#include "PlayerCharacter.h"
#include "UI/GameHUD.h"

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
