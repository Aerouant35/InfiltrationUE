// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSafeZone.h"

#include "PlayerCharacter.h"
#include "Infiltration/InfiltrationGameModeBase.h"

// Sets default values
APlayerSafeZone::APlayerSafeZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	BoxComponent->SetupAttachment(RootComponent);

	CurrentScore = 0.0;

}

// Called when the game starts or when spawned
void APlayerSafeZone::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerSafeZone::OnComponentBeginOverlap);
	
}

// Called every frame
void APlayerSafeZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerSafeZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(APlayerCharacter::StaticClass())) {
		APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
		if(Player->bIsCarrying)
		{
			AFood* Food = Player->DropFood();
			Food->Destroy();
			// Update score and progress bar
			CurrentScore += 1;
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			AGameHUD* GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());
			if(GameHUD)
			{
				GameHUD->UpdateProgressBarPercent(CurrentScore);
			}
			
			if(CurrentScore == Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->GetNbFoodWin())
			{
				GameHUD->ShowVictoryScreen();
				Player->bHasWon = true;
				// Disable user input
				Player->DisableInput(PlayerController);
			}
		}
	}
}

