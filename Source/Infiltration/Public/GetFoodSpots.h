// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodSpot.h"
#include "GameFramework/Actor.h"
#include "GetFoodSpots.generated.h"

UCLASS()
class INFILTRATION_API AGetFoodSpots : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Food")
	TArray<AFoodSpot*> FoodSpots;

public:	
	// Sets default values for this actor's properties
	AGetFoodSpots();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

};
