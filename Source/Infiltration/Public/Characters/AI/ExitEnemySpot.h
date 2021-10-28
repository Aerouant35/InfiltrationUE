// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGoblin.h"
#include "Components/SphereComponent.h"
#include "Engine/TargetPoint.h"
#include "ExitEnemySpot.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AExitEnemySpot : public ATargetPoint
{
	GENERATED_BODY()

	#pragma region Variables
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;
	
	UPROPERTY(VisibleAnywhere)
	uint8 NbEnemies = 0;

	UPROPERTY()
	AAIGoblin* EnemyRef1;

	UPROPERTY()
	AAIGoblin* EnemyRef2;

	UPROPERTY()
	AAIGoblin* EnemyRef3;
	#pragma endregion 

public:
	AExitEnemySpot();
	
	uint8 GetNbEnemies() const { return NbEnemies; }

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UFUNCTION()
	AAIGoblin* DestroyEnemy() const;
};
