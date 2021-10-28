// Fill out your copyright notice in the Description page of Project Settings.


#include "GetMainMenuCamera.h"
#include "Infiltration/MainMenuGameModeBase.h"

// Sets default values
AGetMainMenuCamera::AGetMainMenuCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGetMainMenuCamera::BeginPlay()
{
	Super::BeginPlay();
	
	check(MenuCamera != nullptr);
	Cast<AMainMenuGameModeBase>(GetWorld()->GetAuthGameMode())->SetMainMenuCamera(MenuCamera);

}
