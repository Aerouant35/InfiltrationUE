// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Engine/TargetPoint.h"
#include "EnemySpot.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AEnemySpot : public ATargetPoint
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	AEnemySpot();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	bool HasAFood;

private:

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
