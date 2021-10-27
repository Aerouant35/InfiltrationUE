// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter.h"
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

	UPROPERTY()
	AAICharacter* EnemyRef1;

	UPROPERTY()
	AAICharacter* EnemyRef2;

	UPROPERTY()
	AAICharacter* EnemyRef3;

	FORCEINLINE int GetNumberOfEnemys() const { return NumberOfEnemys; };

	UFUNCTION()
	AAICharacter* DestroyEnemy();

private:

	UPROPERTY(VisibleAnywhere)
	int NumberOfEnemys = 0;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
