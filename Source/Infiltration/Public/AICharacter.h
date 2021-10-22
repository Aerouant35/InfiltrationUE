// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Food.h"
#include "AICharacter.generated.h"

UCLASS()
class INFILTRATION_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category="Spots")
	TArray<AActor*> FoodSpots;

	UPROPERTY(EditAnywhere, Category="Spots")
	AActor* EnemySpot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	float Speed;

	UPROPERTY(EditAnywhere)
	bool IsCarrying;

	UPROPERTY()
	bool IsWalking;

	// Food that AI is close to (OnOverlap)
	AFood* InCollisionFood;
	// Actual food AI is carrying
	AFood* CarryFood;

	FTimerHandle UnusedHandle;

	UPROPERTY(EditAnywhere, Category="Holding Component")
	USceneComponent* HoldingComponent;
	UPROPERTY(EditAnywhere, Category="Holding Component")
	float HoldingComponentOffset = 50.f;

	UPROPERTY(EditAnywhere, Category="Character Speed")
	float DefaultSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category="Pick Up Animation")
	UAnimSequence* PickUpAnimationSequence;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	bool GetISCarrying();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void TimerPickUpAnim();

	UFUNCTION()
		void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
