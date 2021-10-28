// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Food.h"
#include "AIGoblin.generated.h"

UCLASS()
class INFILTRATION_API AAIGoblin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGoblin();

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* DefaultBehaviorTree;

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* ChaseBehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	bool HasFood;

	bool bHasWon = false;
	bool bHasLost = false;

	// Bool qui defini si l'IA doit aller dans les spots sans nourriture
	UPROPERTY()
	bool PatrolState;

	UPROPERTY(VisibleAnywhere)
	int NumberOfPatrols;

	// Food that AI is close to (OnOverlap)
	AFood* InCollisionFood;
	// Actual food AI is carrying
	AFood* CarryFood;
	// Food qui a été drop
	AFood* DropFood;

	FTimerHandle UnusedHandle;

	UPROPERTY(EditAnywhere, Category="Holding Component")
		USceneComponent* HoldingComponent;
	UPROPERTY(EditAnywhere, Category="Holding Component")
		float HoldingComponentOffset = 50.f;

	UPROPERTY(VisibleAnywhere, Category="Character Speed")
	float DefaultSpeed = 400;
	UPROPERTY(VisibleAnywhere, Category="Character Speed")
	float CarrySpeed = DefaultSpeed / 2;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimSequence* PickUpAnimationSequence;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
		void Interact();

	UFUNCTION()
		void TimerPickUpAnim();

	UFUNCTION()
		FVector GetCarryFoodLocation();

	UFUNCTION()
	void SetSpeed(float NewSpeed);

	UFUNCTION()
	void SetAnimation(TSubclassOf<UAnimInstance> BP_Anim);

	UFUNCTION()
	void SetHasFood(bool NewValue, AFood* NewFood);

	UFUNCTION()
	void SetPatrolState(bool Activate, int NewNumberOfPatrols);

	UFUNCTION()
	void DecrementNumberOfPatrols();

	FORCEINLINE bool GetHasFood() const { return HasFood; }

	bool GetPatrolState();

	UFUNCTION()
		void HasLost();
	UFUNCTION()
		void HasWon();

	void StopController();

	FORCEINLINE bool GetHasWon() const { return bHasWon; }

	FORCEINLINE bool GetHasLost() const { return bHasLost; }

	FORCEINLINE int GetNumberOfPatrols() const { return NumberOfPatrols; }

	bool GetHasDropFood(); 

	FORCEINLINE USceneComponent* GetHoldingComponent() const { return HoldingComponent; }

	UFUNCTION()
		void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
