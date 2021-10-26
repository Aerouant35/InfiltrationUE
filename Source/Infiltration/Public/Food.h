// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"

UCLASS()
class INFILTRATION_API AFood : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere)
	unsigned SphereRadius = 100.f;
	
public:	
	// Sets default values for this actor's properties
	AFood();

	UFUNCTION()
		void PickUp(USceneComponent* HoldingCompSend);
	UFUNCTION()
		void Drop();

	UFUNCTION()
		void SetPhysics(bool bIsGrab);
	UFUNCTION()
		void SetDynamicCollision(bool bIsGrab);

	FORCEINLINE UStaticMeshComponent* GetStaticMeshComp() const { return StaticMeshComponent; }

protected:

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComp;
	UPROPERTY(EditAnywhere)
	ACharacter* MyCharacter;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
		
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
