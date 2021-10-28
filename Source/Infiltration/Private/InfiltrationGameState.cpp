// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiltrationGameState.h"

AInfiltrationGameState::AInfiltrationGameState()
{
}

void AInfiltrationGameState::IncrementNumberOfFoods()
{
	NumberOfFoods += 1;
}

void AInfiltrationGameState::DecrementNumberOfFoods()
{
	if(NumberOfFoods > 1)
	{
		NumberOfFoods -= 1;
	}
}

void AInfiltrationGameState::IncrementNumberOfEnemys()
{
	NumberOfEnemys += 1;
}

void AInfiltrationGameState::DecrementNumberOfEnemys()
{
	if(NumberOfEnemys > 1)
	{
		NumberOfEnemys -= 1;
	}
}