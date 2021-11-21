// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/AIGoblin.h"
#include "Characters/Player/CharactKnight.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Infiltration/InfiltrationGameModeBase.h"

// Sets default values
AAIGoblin::AAIGoblin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HoldingComponent = CreateDefaultSubobject<USceneComponent>("HoldingComponent");
	HoldingComponent->SetupAttachment(GetCapsuleComponent());
	HoldingComponent->SetRelativeLocation(FVector(HoldingComponentOffset, HoldingComponent->GetRelativeLocation().Y, HoldingComponent->GetRelativeLocation().Z));
}

// Called when the game starts or when spawned
void AAIGoblin::BeginPlay()
{
	Super::BeginPlay();

	// Delegate for overlap
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAIGoblin::OnComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AAIGoblin::OnComponentEndOverlap);

	// Avoid the camera to stop before the enemy
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterMesh"));
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// Don't possess food in the beginning
	SetHasFood(false, nullptr);
}

void AAIGoblin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

#pragma region ProtectedMethod
void AAIGoblin::TimerPickUpAnim() const
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CarryFood->PickUp(HoldingComponent);
}

void AAIGoblin::SetSpeed(const float NewSpeed) const
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}
#pragma endregion 

#pragma region Overlap Methods
void AAIGoblin::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		InCollisionFood = Cast<AFood>(OtherActor);
	}

	// If touch player : game over
	if(OtherActor->IsA(ACharactKnight::StaticClass()))
	{
		// Game Over
		AInfiltrationGameModeBase* InfiltrationGameModeBase = Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode());
		check(InfiltrationGameModeBase != nullptr);
		InfiltrationGameModeBase->Defeat();
	}
}

void AAIGoblin::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		InCollisionFood = nullptr;
	}
}
#pragma endregion 

#pragma region PublicMethod
// Take or drop food close around
void AAIGoblin::Interact()
{
	if(HasFood)
	{
		SetHasFood(false, nullptr);
	}
	else if(InCollisionFood != nullptr)
	{
		SetHasFood(true, InCollisionFood);

		GetMesh()->PlayAnimation(PickUpAnimationSequence, false);
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AAIGoblin::TimerPickUpAnim, PickUpAnimationSequence->SequenceLength, false);
	}
}

FVector AAIGoblin::GetDroppedFoodLocation() const
{
	return DropFood->GetActorLocation();
}

void AAIGoblin::SetAnimation(const TSubclassOf<UAnimInstance> BP_Anim) const
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimClass(BP_Anim);
}

void AAIGoblin::SetHasFood(const bool NewValue, AFood* NewFood)
{
	HasFood = NewValue;
	
	if(NewValue)
	{
		CarryFood = NewFood;
		DropFood = nullptr;
		SetSpeed(DefaultSpeed * 0.5f);
	}
	else
	{
		SetSpeed(DefaultSpeed);

		if (CarryFood != nullptr)
		{
			CarryFood->Drop();
			DropFood = CarryFood;
			CarryFood = nullptr;
		}
	}
}

void AAIGoblin::SetPatrolState(const bool Activate, const uint8 NewNbPatrols)
{
	PatrolState = Activate;
	NbPatrols = NewNbPatrols;
}

void AAIGoblin::DecrementNumberOfPatrols()
{
	NbPatrols--;
	if(NbPatrols <= 0)
	{
		PatrolState = false;
	}
}

// Something to modify
bool AAIGoblin::GetPatrolState() const
{
	if(NbPatrols > 1)
	{
		return true;
	}
	return false;
}

void AAIGoblin::HasLost()
{
	bHasLost = true;
	SetHasFood(false, nullptr);
	StopController();
}

void AAIGoblin::HasWon()
{
	bHasWon = true;
	SetHasFood(false, nullptr);
	StopController();
}

void AAIGoblin::StopController() const
{
	GetController()->UnPossess();
}

bool AAIGoblin::GetHasDropFood() const
{
	if(DropFood != nullptr)
	{
		return true;
	}
	return false;
}
#pragma endregion 
