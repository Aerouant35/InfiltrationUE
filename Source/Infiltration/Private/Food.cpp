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
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFood::PickUp(USceneComponent* HoldingCompSend)
{
	if(!HoldingCompSend)
	{
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, HoldingCompSend->GetOwner()->GetName()); // Fait crash avec IA

	bIsGrab = !bIsGrab;
	bHasGravity = !bHasGravity;
	
	StaticMeshComponent->SetSimulatePhysics(bIsGrab ? false : true);
	StaticMeshComponent->SetEnableGravity(bHasGravity);
	ChangeCollisionPreset();

	HoldingComp = HoldingCompSend;
	
	if(HoldingComp && bIsGrab)
	{
		StaticMeshComponent->AttachToComponent(HoldingComp, FAttachmentTransformRules::KeepWorldTransform);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("PickUp 2"));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, HoldingComp->GetComponentLocation().ToString());
		SetActorLocation(HoldingComp->GetComponentLocation());
	}
	else if(!bIsGrab)
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
