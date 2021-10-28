// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InfiltrationGameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INFILTRATION_API AMainMenuGameModeBase : public AInfiltrationGameModeBase
{
	GENERATED_BODY()
	
	AMainMenuGameModeBase();

public:
	void SetMainMenuCamera(ACameraActor* MenuCamera) const;
};
