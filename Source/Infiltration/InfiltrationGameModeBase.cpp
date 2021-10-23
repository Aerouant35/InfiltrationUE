// Copyright Epic Games, Inc. All Rights Reserved.


#include "InfiltrationGameModeBase.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UI/GameHUD.h"

AInfiltrationGameModeBase::AInfiltrationGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	HUDClass = AGameHUD::StaticClass();
	PlayerControllerClass = APlayerController::StaticClass();
	GameHUDClass = Cast<AGameHUD>(HUDClass);
}

void AInfiltrationGameModeBase::Victory()
{
	GameHUDClass->ShowVictoryScreen();
}

void AInfiltrationGameModeBase::Defeat()
{
	GameHUDClass->ShowDefeatScreen();
}
