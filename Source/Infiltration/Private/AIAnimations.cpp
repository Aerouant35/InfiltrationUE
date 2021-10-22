// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAnimations.h"

#include "AICharacter.h"


UAIAnimations::UAIAnimations()
{
	IsWalking = false;
}


void UAIAnimations::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if(Pawn)
	{
		AAICharacter* AIChar = Cast<AAICharacter>(Pawn);
		if(AIChar)
		{
			IsWalking = !AIChar->GetVelocity().IsZero();
			IsCarrying = AIChar->GetISCarrying();
		}
	}
}