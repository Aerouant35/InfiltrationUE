// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerSafeZone.generated.h"

UCLASS()
class INFILTRATION_API APlayerSafeZone : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* BoxComponent;
		
public:	
	// Sets default values for this actor's properties
	APlayerSafeZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	private:

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


};
