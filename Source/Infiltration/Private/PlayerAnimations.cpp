// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimations.h"

#include "PlayerCharacter.h"


UPlayerAnimations::UPlayerAnimations()
{
	bIsWalking = false;
}


void UPlayerAnimations::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if(Pawn)
	{
		APlayerCharacter* MyCharacter = Cast<APlayerCharacter>(Pawn);
		if(MyCharacter)
		{
			bIsWalking = !MyCharacter->GetVelocity().IsZero();
			bIsCarrying = MyCharacter->bIsCarrying;
			bHasWon = MyCharacter->bHasWon;
			bHasLost = MyCharacter->bHasLost;
		}
	}
}
