// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

AMyGameState::AMyGameState()
{
	
}

bool AMyGameState::ThereIsAFreeFoodSpot()
{
	for (AFoodSpot* FoodSpot : FoodSpots)
	{
		if(!FoodSpot->HasAFood)
		{
			return true;
		}
	}
	return false;
}