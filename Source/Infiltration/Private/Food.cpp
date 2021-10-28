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
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->SetSphereRadius(SphereRadius);
	// Ignore collision with the camera
	SetDynamicCollision(false);
	
	SphereComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFood::PickUp(USceneComponent* HoldingCompSend)
{
	SetPhysics(true);

	HoldingComp = HoldingCompSend;
	
	if(HoldingComp)
	{
		StaticMeshComponent->AttachToComponent(HoldingComp, FAttachmentTransformRules::KeepWorldTransform);
		SetActorLocation(HoldingComp->GetComponentLocation());
	}
}

void AFood::Drop()
{
	SetPhysics(false);

	StaticMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void AFood::SetPhysics(bool bIsGrab)
{
	StaticMeshComponent->SetSimulatePhysics(!bIsGrab);
	StaticMeshComponent->SetEnableGravity(!bIsGrab);

	SetDynamicCollision(bIsGrab);
}

void AFood::SetDynamicCollision(bool bIsGrab)
{
	StaticMeshComponent->SetCollisionProfileName(bIsGrab ? TEXT("NoCollision") : TEXT("BlockAllDynamic"));
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}