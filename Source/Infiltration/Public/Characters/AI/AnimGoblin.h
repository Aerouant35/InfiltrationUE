// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimGoblin.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UAnimGoblin : public UAnimInstance
{
	GENERATED_BODY()

	#pragma region Variables
	UPROPERTY(VisibleAnywhere)
	bool IsWalking;

	UPROPERTY(VisibleAnywhere)
	bool IsCarrying;

	UPROPERTY(VisibleAnywhere)
	bool HasLost;

	UPROPERTY(VisibleAnywhere)
	bool HasWon;
	#pragma endregion
	
public:
	UAnimGoblin();
	
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
