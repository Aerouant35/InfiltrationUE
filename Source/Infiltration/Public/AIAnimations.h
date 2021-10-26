// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AIAnimations.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UAIAnimations : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAIAnimations();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsWalking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCarrying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasLost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasWon;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};