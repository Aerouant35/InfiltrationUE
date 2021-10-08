// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"


UMyAnimInstance::UMyAnimInstance()
{
	bIsWalking = false;
}


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if(Pawn)
	{
		bIsWalking = !Pawn->GetVelocity().IsZero();
	}
}
