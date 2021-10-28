// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimKnight.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UAnimKnight : public UAnimInstance
{
	GENERATED_BODY()

	public:
	UAnimKnight();
	
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
