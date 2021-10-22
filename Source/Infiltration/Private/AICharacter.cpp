// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	// Delegate pour collision de la capsule
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AAICharacter::OnComponentEndOverlap);

	// Ne possède pas de nourriture de base
	IsCarrying = false;

	IsWalking = false;
	
	Speed = DefaultSpeed;
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAICharacter::GetISCarrying()
{
	return IsCarrying;
}

// Prend ou dépose la nourriture à proximité
void AAICharacter::Interact()
{
	if(IsCarrying)
	{
		IsCarrying = false;
		Speed = DefaultSpeed;

		// Dépose la nourritre
		CarryFood->PickUp();
	}
	else if(InCollisionFood != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("PickUp"));

		IsCarrying = true;
		Speed = DefaultSpeed * 0.5f;
		// Va prendre la nourriture avec laquel je collisionne
		CarryFood = InCollisionFood;

		GetMesh()->PlayAnimation(PickUpAnimationSequence, false);
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AAICharacter::TimerPickUpAnim, PickUpAnimationSequence->SequenceLength, false);
	}
}

void AAICharacter::TimerPickUpAnim()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CarryFood->PickUp();

	//bIsPickingUp = false;
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Collisions
void AAICharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		InCollisionFood = Cast<AFood>(OtherActor);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("In areafood"));
	}

	// Si touche joueur : défaite
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		// Game Over
	}
}

void AAICharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		InCollisionFood = nullptr;
	}
}

