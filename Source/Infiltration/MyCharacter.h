// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class INFILTRATION_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	private:
	void HorizontalMove(float Value);
	void VerticalMove(float Value);

	void HorizontalRotation(float Value);
	void VerticalRotation(float Value);

	void Zoom(float Value);

	UPROPERTY(EditAnywhere, Category="Zoom")
		float ZoomInMax = 140;
	UPROPERTY(EditAnywhere, Category="Zoom")
		float ZoomOutMax = 310;

	UPROPERTY()
		USpringArmComponent* SpringArmComponent;
	UPROPERTY()
		UCameraComponent* CameraComponent;
	
};
