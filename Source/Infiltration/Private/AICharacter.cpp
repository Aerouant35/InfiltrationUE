// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HoldingComponent = CreateDefaultSubobject<USceneComponent>("HoldingComponent");
	HoldingComponent->SetupAttachment(GetCapsuleComponent());
	HoldingComponent->SetRelativeLocation(FVector(HoldingComponentOffset, HoldingComponent->GetRelativeLocation().Y, HoldingComponent->GetRelativeLocation().Z));
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	// Delegate pour collision de la capsule
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AAICharacter::OnComponentEndOverlap);

	// Ne possède pas de nourriture de base
	SetHasFood(false, nullptr);
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Prend ou dépose la nourriture à proximité
void AAICharacter::Interact()
{
	if(HasFood)
	{
		SetHasFood(false, nullptr);
	}
	else if(InCollisionFood != nullptr)
	{
		SetHasFood(true, InCollisionFood);

		GetMesh()->PlayAnimation(PickUpAnimationSequence, false);
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AAICharacter::TimerPickUpAnim, PickUpAnimationSequence->SequenceLength, false);
	}
}

void AAICharacter::SetHasFood(bool Value, AFood* NewFood)
{
	HasFood = Value;
	if(Value)
	{
		CarryFood = NewFood;
		SetSpeed(DefaultSpeed * 0.5f);
	}
	else
	{
		SetSpeed(DefaultSpeed);

		if(CarryFood != nullptr)
		{
			CarryFood->Drop();
		}
	}
}

void AAICharacter::TimerPickUpAnim()
{
	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CarryFood->PickUp(HoldingComponent);
}

FVector AAICharacter::GetCarryFoodLocation()
{
	return CarryFood->GetActorLocation();
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::SetSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AAICharacter::SetAnimation(TSubclassOf<UAnimInstance> BP_Anim)
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimClass(BP_Anim);
}

// Collisions
void AAICharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		InCollisionFood = Cast<AFood>(OtherActor);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("In areafood"));
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

