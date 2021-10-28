// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfiltrationGameState.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Infiltration/InfiltrationGameModeBase.h"
#include "PlayerSafeZone.generated.h"

USTRUCT()
struct FFoodShelf
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<AActor*> FoodMeshes;
};

UCLASS()
class INFILTRATION_API APlayerSafeZone : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FFoodShelf> FoodShelves;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY()
	AInfiltrationGameModeBase* InfiltrationGameModeBase;

	UPROPERTY()
	AInfiltrationGameState* InfiltrationGameState;
		
public:	
	// Sets default values for this actor's properties
	APlayerSafeZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void FillShelf(uint8 CurrentFood);

};
