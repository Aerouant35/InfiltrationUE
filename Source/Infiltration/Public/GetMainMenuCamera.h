// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GetMainMenuCamera.generated.h"

UCLASS()
class INFILTRATION_API AGetMainMenuCamera : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class ACameraActor* MenuCamera;

public:	
	// Sets default values for this actor's properties
	AGetMainMenuCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
