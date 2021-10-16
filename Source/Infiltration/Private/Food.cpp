// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->BodyInstance.bLockXRotation = true;
	StaticMeshComponent->BodyInstance.bLockYRotation = true;
	StaticMeshComponent->BodyInstance.bLockZRotation = true;
	StaticMeshComponent->SetupAttachment(RootComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->InitSphereRadius(SphereRadius);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	SphereComponent->SetupAttachment(StaticMeshComponent);

	bIsGrab = false;
	bHasGravity = true;

}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->SetSphereRadius(SphereRadius);
	// Ignore collision with the camera
	ChangeCollisionPreset();

	// -- Not sure if this is good --
	MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	TArray<USceneComponent*> Components;
	MyCharacter->GetComponents(Components);
	if(Components.Num() > 0)
	{
		for(USceneComponent* Comp : Components)
		{
			if(Comp->GetName() == "HoldingComponent")
			{
				HoldingComp = Cast<USceneComponent>(Comp);
			}
		}
	}	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFood::PickUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("PickUp"));

	bIsGrab = !bIsGrab;
	bHasGravity = !bHasGravity;
	
	StaticMeshComponent->SetSimulatePhysics(bIsGrab ? false : true);
	StaticMeshComponent->SetEnableGravity(bHasGravity);
	ChangeCollisionPreset();

	
	if(HoldingComp && bIsGrab)
	{
		StaticMeshComponent->AttachToComponent(HoldingComp, FAttachmentTransformRules::KeepWorldTransform);
		SetActorLocation(HoldingComp->GetComponentLocation());
	}
	if(!bIsGrab)
	{
		StaticMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void AFood::ChangeCollisionPreset()
{
	StaticMeshComponent->SetCollisionProfileName(bIsGrab ? TEXT("NoCollision") : TEXT("BlockAllDynamic"));
	// Ignore collision with the camera
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}
