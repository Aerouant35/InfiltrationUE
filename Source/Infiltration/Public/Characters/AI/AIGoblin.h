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

	#pragma region Variables
	// Bool who define if AI go to spot without foods
	bool PatrolState;
	bool HasFood;
	bool bHasWon = false;
	bool bHasLost = false;
	
	FTimerHandle UnusedHandle;

	// Food that AI is close to (OnOverlap)
	UPROPERTY()
	AFood* InCollisionFood;
	
	// Actual food AI is carrying
	UPROPERTY()
	AFood* CarryFood;
	
	// Food who was drop
	UPROPERTY()
	AFood* DropFood;

	UPROPERTY(VisibleAnywhere)
	uint8 NbPatrols;

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* DefaultBehaviorTree;

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* ChaseBehaviorTree;
	
	UPROPERTY(EditAnywhere, Category="Holding Component")
	USceneComponent* HoldingComponent;
	
	UPROPERTY(EditAnywhere, Category="Holding Component")
	float HoldingComponentOffset = 50.f;

	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimSequence* PickUpAnimationSequence;

	UPROPERTY(VisibleAnywhere, Category="Character Speed")
	float DefaultSpeed = 400;
	#pragma endregion 
	
public:
	// Sets default values for this character's properties
	AAIGoblin();

	#pragma region Accessor
	bool GetHasFood() const { return HasFood; }
	
	bool GetHasWon() const { return bHasWon; }

	bool GetHasLost() const { return bHasLost; }

	uint8 GetNumberOfPatrols() const { return NbPatrols; }

	UBehaviorTree* GetDefaultBehaviourTree() const { return DefaultBehaviorTree; }
	
	UBehaviorTree* GetChaseBehaviourTree() const { return ChaseBehaviorTree; }
	
	USceneComponent* GetHoldingComponent() const { return HoldingComponent; }
	#pragma endregion 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	#pragma region ProtectedMethod
	UFUNCTION()
	void TimerPickUpAnim() const;

	UFUNCTION()
	void SetSpeed(float NewSpeed) const;
	#pragma endregion 

	#pragma region Overlap Methods
	UFUNCTION()
	void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	#pragma endregion
	
public:
	#pragma region PublicMethod
	UFUNCTION()
	void Interact();

	UFUNCTION()
	FVector GetDroppedFoodLocation() const;

	UFUNCTION()
	void SetAnimation(TSubclassOf<UAnimInstance> BP_Anim) const;

	UFUNCTION()
	void SetHasFood(bool NewValue, AFood* NewFood);

	UFUNCTION()
	void SetPatrolState(bool Activate, uint8 NewNbPatrols);

	UFUNCTION()
	void DecrementNumberOfPatrols();
	
	bool GetPatrolState() const;

	UFUNCTION()
	void HasLost();
	
	UFUNCTION()
	void HasWon();

	void StopController() const;

	bool GetHasDropFood() const;
	#pragma endregion 
};
