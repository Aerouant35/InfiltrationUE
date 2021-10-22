// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/GameHUD.h"
#include "InfiltrationGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AInfiltrationGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AGameHUD* GameHUDClass;
	
	UPROPERTY(EditDefaultsOnly)
	unsigned NbFoodWin = 5;
public:
	unsigned GetNbFoodWin() const
	{
		return NbFoodWin;
	}

	AInfiltrationGameModeBase();
	
	void Victory();

	void Defeat();
	
};
