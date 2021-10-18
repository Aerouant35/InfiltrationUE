// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSafeZone.h"

#include "PlayerCharacter.h"

// Sets default values
APlayerSafeZone::APlayerSafeZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	BoxComponent->SetupAttachment(RootComponent);

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
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Player have food"));
			AFood* Food = Player->DropFood();
			Food->Destroy();
			// Update score

			// Test si score == NbFoodWin
			// Yes --> Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->Victory();
		}
	}
}

