// Copyright Epic Games, Inc. All Rights Reserved.


#include "InfiltrationGameModeBase.h"

#include "PlayerCharacter.h"
#include "UI/GameHUD.h"

AInfiltrationGameModeBase::AInfiltrationGameModeBase()
{
		DefaultPawnClass = APlayerCharacter::StaticClass();
		HUDClass = AGameHUD::StaticClass();
}
