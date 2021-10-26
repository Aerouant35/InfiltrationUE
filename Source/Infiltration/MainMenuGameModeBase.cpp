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

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ACameraActor> CamItr(GetWorld()); CamItr; ++CamItr)
	{
		if (CamItr->ActorHasTag("MenuCamera"))
		{
			MenuCamera = *CamItr;
		}
	}

	GetWorld()->GetFirstPlayerController()->SetViewTarget(MenuCamera);
}
