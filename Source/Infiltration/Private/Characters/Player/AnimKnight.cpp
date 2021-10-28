// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/AnimKnight.h"
#include "Characters/Player/CharactKnight.h"

UAnimKnight::UAnimKnight()
{
}

void UAnimKnight::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = UAnimInstance::TryGetPawnOwner();
	if(Pawn == nullptr) return;

	CharactKnight = Cast<ACharactKnight>(Pawn);
	check(CharactKnight != nullptr);
	
	bIsWalking = !CharactKnight->GetVelocity().IsZero();
	bIsCarrying = CharactKnight->GetIsCarrying();;
	bHasWon = CharactKnight->GetHasWon();
	bHasLost = CharactKnight->GetHasLost();
}
