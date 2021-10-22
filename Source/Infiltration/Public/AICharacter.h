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

	UPROPERTY(VisibleAnywhere, Category="Character Speed")
	float DefaultSpeed = 600;
	UPROPERTY(VisibleAnywhere, Category="Character Speed")
	float CarrySpeed = DefaultSpeed / 2;

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
	void SetSpeed(float NewSpeed);

	UFUNCTION()
		void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
