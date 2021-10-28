// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"

#include "EngineUtils.h"
#include "PlayerCharacter.h"
#include "Camera/CameraActor.h"
#include "UI/Menu/MainMenuHUD.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	HUDClass = AMainMenuHUD::StaticClass();
}

void AMainMenuGameModeBase::SetMainMenuCamera(ACameraActor* MenuCamera) const
{
	GetWorld()->GetFirstPlayerController()->SetViewTarget(MenuCamera);
}
