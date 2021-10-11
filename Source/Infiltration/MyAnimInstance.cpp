// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MyCharacter.h"


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
		AMyCharacter* MyCharacter = Cast<AMyCharacter>(Pawn);
		if(MyCharacter)
		{
			bIsWalking = !MyCharacter->GetVelocity().IsZero();
			bIsCarrying = MyCharacter->bIsCarrying;
		}
	}
}
