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
	
	AFood* InCollisionFood;
	AFood* CarryFood;

	FTimerHandle UnusedHandle;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void HorizontalRotation(float Value);
	void VerticalRotation(float Value);
	
	void Zoom(float Value);
	void Interact();
	
	UPROPERTY(EditAnywhere, Category="Character Speed")
		float Speed;
	
	UPROPERTY(EditAnywhere, Category="Camera Speed")
		float TurnRate;
	UPROPERTY(EditAnywhere, Category="Camera Speed")
		float LookUpRate;

	UPROPERTY(EditAnywhere, Category="Zoom")
		float ZoomInMax = 200;
	UPROPERTY(EditAnywhere, Category="Zoom")
		float ZoomOutMax = 700;

	UPROPERTY(EditAnywhere, Category="Pick Up Animation")
		UAnimationAsset* AnimationAsset;

	UPROPERTY()
		USpringArmComponent* SpringArmComponent;
	UPROPERTY()
		UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
		USceneComponent* HoldingComp;		
	
	UFUNCTION()
		void TimerPickUpAnim();

	UFUNCTION()
		void OnComponentBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};


