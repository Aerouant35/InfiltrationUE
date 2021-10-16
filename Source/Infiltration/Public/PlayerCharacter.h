// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class INFILTRATION_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category="Animation boolean")
		bool bIsCarrying;

	private:
	
	bool bIsPickingUp;
	bool bCanPickUp;

	// Food that we are close to (OnOverlap)
	AFood* InCollisionFood;
	// Actual food we are carrying
	AFood* CarryFood;

	FTimerHandle UnusedHandle;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void HorizontalRotation(float Value);
	void VerticalRotation(float Value);
	
	void Zoom(float Value);
	void Interact();
	
	float CurrentSpeed;
	float DefaultSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category="Character Speed")
		float WalkSpeed = 500.f;
	
	UPROPERTY(EditAnywhere, Category="Camera Speed")
		float TurnRate = 45.f;
	UPROPERTY(EditAnywhere, Category="Camera Speed")
		float LookUpRate = 45.f;

	UPROPERTY(EditAnywhere, Category="Zoom")
		float ZoomInMax = 600.f;
	UPROPERTY(EditAnywhere, Category="Zoom")
		float ZoomOutMax = 1000.f;

	UPROPERTY(EditAnywhere, Category="Pick Up Animation")
		UAnimSequence* PickUpAnimationSequence;

	UPROPERTY(EditAnywhere, Category="Holding Component")
		USceneComponent* HoldingComponent;
	UPROPERTY(EditAnywhere, Category="Holding Component")
		float HoldingComponentOffset = 50.f;

	// Speed in which the mesh rotate to be in the same direction as the movement
	UPROPERTY(EditAnywhere, Category="Rotation")
		FRotator RotationRate = FRotator(0.f, 540.f, 0.f);

	UPROPERTY()
		USpringArmComponent* SpringArmComponent;
	UPROPERTY()
		UCameraComponent* CameraComponent;
	
	UFUNCTION()
		void TimerPickUpAnim();

	UFUNCTION()
		void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};


