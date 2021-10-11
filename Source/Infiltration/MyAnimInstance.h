// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	public:
	UMyAnimInstance();
	
	protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsWalking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsCarrying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasLost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasWon;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
