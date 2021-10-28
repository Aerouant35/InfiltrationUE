// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

AMyGameState::AMyGameState()
{
}

void AMyGameState::IncrementFood()
{
	NumberOfFoods += 1;
}

void AMyGameState::DecrementFood()
{
	if(NumberOfFoods > 1)
	{
		NumberOfFoods -= 1;
	}
}