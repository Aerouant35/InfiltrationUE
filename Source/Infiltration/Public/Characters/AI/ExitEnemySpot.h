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

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	AExitEnemySpot();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AAIGoblin* EnemyRef1;

	UPROPERTY()
	AAIGoblin* EnemyRef2;

	UPROPERTY()
	AAIGoblin* EnemyRef3;

	FORCEINLINE int GetNumberOfEnemys() const { return NumberOfEnemys; };

	UFUNCTION()
	AAIGoblin* DestroyEnemy();

private:

	UPROPERTY(VisibleAnywhere)
	int NumberOfEnemys = 0;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
