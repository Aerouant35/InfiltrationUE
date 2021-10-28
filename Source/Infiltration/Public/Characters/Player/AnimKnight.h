// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharactKnight.h"
#include "Animation/AnimInstance.h"
#include "AnimKnight.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API UAnimKnight : public UAnimInstance
{
	GENERATED_BODY()

	#pragma region Variables
	UPROPERTY(VisibleAnywhere)
	bool bIsWalking;

	UPROPERTY(VisibleAnywhere)
	bool bIsCarrying;

	UPROPERTY(VisibleAnywhere)
	bool bHasLost;

	UPROPERTY(VisibleAnywhere)
	bool bHasWon;

	UPROPERTY()
	ACharactKnight* CharactKnight;
	#pragma endregion

public:
	UAnimKnight();
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
