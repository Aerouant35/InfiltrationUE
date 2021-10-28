// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerSafeZone.h"
#include "InfiltrationGameState.h"
#include "Characters/Player/CharactKnight.h"
#include "Infiltration/InfiltrationGameModeBase.h"

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

	for (auto Food : FoodShelves)
	{
		for (const auto FoodMesh : Food.FoodMeshes)
		{
			const auto StaticMeshComp = FoodMesh->FindComponentByClass<UStaticMeshComponent>();
			StaticMeshComp->SetVisibility(false);
		}
	}
}

// Called every frame
void APlayerSafeZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerSafeZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(ACharactKnight::StaticClass())) {
		ACharactKnight* Player = Cast<ACharactKnight>(OtherActor);
		if(Player->GetIsCarrying())
		{
			AFood* Food = Player->DropFood();
			Food->Destroy();

			Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->IncrementFood();

			FillShelf(Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->GetCurrentNbFood());

			// Decremente la food au state
			Cast<AInfiltrationGameState>(GetWorld()->GetGameState())->DecrementFood();
		}
	}
}

void APlayerSafeZone::FillShelf(uint8 CurrentFood)
{
	for (uint8 i = 0; i < FoodShelves.Num(); i++)
	{
		if (i != CurrentFood - 1) continue;
		for (const auto FoodMesh : FoodShelves[i].FoodMeshes)
		{
			const auto StaticMeshComp = FoodMesh->FindComponentByClass<UStaticMeshComponent>();
			StaticMeshComp->SetVisibility(true);
		}
	}
}

