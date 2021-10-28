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

	// Delegate pour collision de la capsule
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAIGoblin::OnComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AAIGoblin::OnComponentEndOverlap);

	// Avoid the camera to stop before the enemy
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterMesh"));
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// Ne possède pas de nourriture de base
	SetHasFood(false, nullptr);
}

// Called every frame
void AAIGoblin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Prend ou dépose la nourriture à proximité
void AAIGoblin::Interact()
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Interact"));
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

void AAIGoblin::SetHasFood(bool NewValue, AFood* NewFood)
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

		if(CarryFood != nullptr)
		{
			CarryFood->Drop();
			DropFood = CarryFood;
			CarryFood = nullptr;
		}
	}
}

void AAIGoblin::SetPatrolState(bool Activate, int NewNumberOfPatrols)
{
	PatrolState = Activate;
	NumberOfPatrols = NewNumberOfPatrols;
}

void AAIGoblin::DecrementNumberOfPatrols()
{
	NumberOfPatrols--;
	if(NumberOfPatrols <= 0)
	{
		PatrolState = false;
	}
}

bool AAIGoblin::GetPatrolState()
{
	if(NumberOfPatrols > 1)
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

bool AAIGoblin::GetHasDropFood()
{
	if(DropFood != nullptr)
	{
		return true;
	}
	return false;
}

void AAIGoblin::StopController()
{
	GetController()->UnPossess();
}


void AAIGoblin::TimerPickUpAnim()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CarryFood->PickUp(HoldingComponent);
}

FVector AAIGoblin::GetCarryFoodLocation()
{
	return DropFood->GetActorLocation();
}

// Called to bind functionality to input
void AAIGoblin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAIGoblin::SetSpeed(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}

void AAIGoblin::SetAnimation(TSubclassOf<UAnimInstance> BP_Anim)
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimClass(BP_Anim);
}

// Collisions
void AAIGoblin::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		InCollisionFood = Cast<AFood>(OtherActor);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("In areafood"));
	}

	// Si touche joueur : défaite
	if(OtherActor->IsA(ACharactKnight::StaticClass()))
	{
		// Game Over
		Cast<AInfiltrationGameModeBase>(GetWorld()->GetAuthGameMode())->Defeat();
	}
}

void AAIGoblin::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		InCollisionFood = nullptr;
	}
}

