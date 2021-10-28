// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/AnimKnight.h"
#include "Characters/Player/CharactKnight.h"

UAnimKnight::UAnimKnight()
{
	bIsWalking = false;
}

void UAnimKnight::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if(Pawn)
	{
		ACharactKnight* MyCharacter = Cast<ACharactKnight>(Pawn);
		if(MyCharacter)
		{
			bIsWalking = !MyCharacter->GetVelocity().IsZero();
			bIsCarrying = MyCharacter->GetIsCarrying();;
			bHasWon = MyCharacter->GetHasWon();
			bHasLost = MyCharacter->GetHasLost();
		}
	}
}