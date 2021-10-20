// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"

#include "UI/MainMenuHUD.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	HUDClass = AMainMenuHUD::StaticClass();
}
