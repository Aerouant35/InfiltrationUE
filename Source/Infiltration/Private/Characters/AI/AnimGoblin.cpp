// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/AnimGoblin.h"
#include "Characters/AI/AIGoblin.h"


UAnimGoblin::UAnimGoblin()
{
	IsWalking = false;
}


void UAnimGoblin::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = UAnimInstance::TryGetPawnOwner();
	if(Pawn == nullptr) return;
	
	AAIGoblin* AIChar = Cast<AAIGoblin>(Pawn);
	check(AIChar != nullptr);
	
	IsWalking = !AIChar->GetVelocity().IsZero();
	IsCarrying = AIChar->GetHasFood();
	HasWon = AIChar->GetHasWon();
	HasLost = AIChar->GetHasLost();
}