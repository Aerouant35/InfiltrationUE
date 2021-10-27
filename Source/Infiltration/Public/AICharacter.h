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
	class UBehaviorTree* DefaultBehaviorTree;

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* ChaseBehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	bool HasFood;

	UPROPERTY()
		bool bHasWon = false;
	UPROPERTY()
		bool bHasLost = false;

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
	
	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimSequence* PickUpAnimationSequence;

	UFUNCTION()
	void StopController();
	
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
	void SetHasFood(bool Value, AFood* NewFood);

	UFUNCTION()
		bool GetHasLost();
	UFUNCTION()
		bool GetHasWon();

	UFUNCTION()
		void HasLost();
	UFUNCTION()
		void HasWon();


	FORCEINLINE bool GetHasFood() const { return HasFood; }

	FORCEINLINE USceneComponent* GetHoldingComponent() const { return HoldingComponent; }

	UFUNCTION()
		void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
