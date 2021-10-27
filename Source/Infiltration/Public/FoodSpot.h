// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "Components/SphereComponent.h"
#include "Engine/TargetPoint.h"
#include "FoodSpot.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AFoodSpot : public ATargetPoint
{
	GENERATED_BODY()

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;
	
public:

	AFoodSpot();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	bool HasAFood;

	UPROPERTY()
	AFood* FirstFood;

	UPROPERTY()
	AFood* SecondFood;

	FORCEINLINE int GetNumberOfFoods() const { return NumberOfFoods; };

private:

	UPROPERTY(VisibleAnywhere)
	int NumberOfFoods = 0;
	
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
