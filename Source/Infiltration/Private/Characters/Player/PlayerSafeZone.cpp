// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerSafeZone.h"
#include "InfiltrationGameState.h"
#include "Characters/Player/CharactKnight.h"
#include "Infiltration/InfiltrationGameModeBase.h"

// Sets default values
APlayerSafeZone::APlayerSafeZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerSafeZone::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerSafeZone::OnComponentBeginOverlap);

	InfiltrationGameModeBase = Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode());
	check(InfiltrationGameModeBase != nullptr);

	InfiltrationGameState = Cast<AInfiltrationGameState>(GetWorld()->GetGameState());
	check(InfiltrationGameState != nullptr);

	for (auto Food : FoodShelves)
	{
		for (const auto FoodMesh : Food.FoodMeshes)
		{
			const auto StaticMeshComp = FoodMesh->FindComponentByClass<UStaticMeshComponent>();
			StaticMeshComp->SetVisibility(false);
		}
	}
}

void APlayerSafeZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(ACharactKnight::StaticClass())) {
		ACharactKnight* Player = Cast<ACharactKnight>(OtherActor);
		
		if(Player->GetIsCarrying())
		{
			AFood* Food = Player->DropFood();
			check(Food != nullptr);
			Food->Destroy();

			InfiltrationGameModeBase->IncrementFood();
			
			FillShelf(InfiltrationGameModeBase->GetCurrentNbFood());

			// Decrement food in global state
			InfiltrationGameState->DecrementNumberOfFoods();
		}
	}
}

void APlayerSafeZone::FillShelf(const uint8 CurrentFood)
{
	for (uint8 i = 0; i < FoodShelves.Num(); i++)
	{
		if (i != CurrentFood - 1) continue;
		for (const auto FoodMesh : FoodShelves[i].FoodMeshes)
		{
			if(!FoodMesh) return;
			const auto StaticMeshComp = FoodMesh->FindComponentByClass<UStaticMeshComponent>();
			StaticMeshComp->SetVisibility(true);
		}
	}
}

