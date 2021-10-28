// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiltrationGameState.h"

AInfiltrationGameState::AInfiltrationGameState()
{
}

void AInfiltrationGameState::IncrementFood()
{
	NumberOfFoods += 1;
}

void AInfiltrationGameState::DecrementFood()
{
	if(NumberOfFoods > 1)
	{
		NumberOfFoods -= 1;
	}
}