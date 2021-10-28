// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "CharactKnight.generated.h"

UCLASS()
class INFILTRATION_API ACharactKnight : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY()
	bool bIsPickingUp;

	UPROPERTY()
	bool bCanPickUp;

	UPROPERTY()
	float CurrentSpeed;

	UPROPERTY()
	float DefaultSpeed = 1.f;

	// Food that we are close to (OnOverlap)
	UPROPERTY()
	AFood* InCollisionFood;
	
	// Actual food we are carrying
	UPROPERTY()
	AFood* CarryFood;

	UPROPERTY(VisibleAnywhere)
	bool bHasWon = false;
	
	UPROPERTY(VisibleAnywhere)
	bool bHasLost = false;

	UPROPERTY()
	FTimerHandle UnusedHandle;

	#pragma region EditorVariables
	UPROPERTY(VisibleAnywhere, Category="Animation boolean")
	bool bIsCarrying;

	UPROPERTY(EditAnywhere, Category="Character Speed")
	float WalkSpeed = 500.f;
	
	UPROPERTY(EditAnywhere, Category="Camera Speed")
	float TurnRate = 45.f;
	
	UPROPERTY(EditAnywhere, Category="Camera Speed")
	float LookUpRate = 45.f;

	UPROPERTY(EditAnywhere, Category="Zoom")
	float ZoomInMax = 200.f;
	
	UPROPERTY(EditAnywhere, Category="Zoom")
	float ZoomOutMax = 600.f;

	UPROPERTY(EditAnywhere, Category="Pick Up Animation")
	UAnimSequence* PickUpAnimationSequence;

	UPROPERTY(VisibleAnywhere, Category="Holding Component")
	USceneComponent* HoldingComponent;
	
	UPROPERTY(EditAnywhere, Category="Holding Component")
	float HoldingComponentOffset = 50.f;
	
	// Speed in which the mesh rotate to be in the same direction as the movement
	UPROPERTY(EditAnywhere, Category="Rotation")
	FRotator RotationRate = FRotator(0.f, 540.f, 0.f);
	#pragma endregion

	UPROPERTY(EditDefaultsOnly)
	UAIPerceptionStimuliSourceComponent* StimuliSource;
	
	UPROPERTY()
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY()
	UCameraComponent* CameraComponent;
public:
	// Sets default values for this character's properties
	ACharactKnight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	AFood* DropFood();

	UFUNCTION()
	void HasWon();
	
	UFUNCTION()
	void HasLost();

	UFUNCTION()
	void StopMovement();
	
	UFUNCTION()
	bool GetHasWon() const { return bHasWon; }
	
	UFUNCTION()
	bool GetHasLost() const { return bHasLost; }
	
	UFUNCTION()
	bool GetIsCarrying() const { return bIsCarrying; }
		
private:
	
	#pragma region Delegate Methods
	void MoveForward(const float Value);
	
	void MoveRight(const float Value);
	
	void HorizontalRotation(const float Value);
	
	void VerticalRotation(const float Value);
	
	void Zoom(const float Value);
	
	void Interact();

	void PauseGame();
	#pragma endregion
	
	#pragma region Overlap Methods
	UFUNCTION()
	void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	#pragma endregion

	UFUNCTION()
	void TimerPickUpAnim();
};


