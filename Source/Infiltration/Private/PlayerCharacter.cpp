// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Level/GameHUD.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = ZoomInMax;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bDoCollisionTest = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	HoldingComponent = CreateDefaultSubobject<USceneComponent>("HoldingComponent");
	HoldingComponent->SetRelativeLocation(FVector(HoldingComponentOffset, HoldingComponent->GetRelativeLocation().Y, HoldingComponent->GetRelativeLocation().Z));
	HoldingComponent->SetupAttachment(GetCapsuleComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));

	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("PerceptionStimuliSource"));
	StimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	StimuliSource->RegisterWithPerceptionSystem();
	
	bIsCarrying = false;
	bIsPickingUp = false;
	bCanPickUp = false;

	CurrentSpeed = DefaultSpeed;

	InCollisionFood = nullptr;
	CarryFood = nullptr;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnComponentEndOverlap);

	GetCharacterMovement()->RotationRate = RotationRate;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Zoom", this, &APlayerCharacter::Zoom);
	
	PlayerInputComponent->BindAxis("HorizontalRotation", this, &APlayerCharacter::HorizontalRotation);
	PlayerInputComponent->BindAxis("VerticalRotation", this, &APlayerCharacter::VerticalRotation);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::PauseGame);

}

void APlayerCharacter::MoveForward(float Value)
{
	if(!bIsPickingUp && Controller != nullptr && Value != 0)
	{
		// Get the Rotation of the Controller as this may not be the same as the camera
		FRotator Rotation = Controller->GetControlRotation();
		// We only want the Yaw part
		FRotator Yaw = FRotator(0, Rotation.Yaw, 0);
		// Get the forward vector of the Rotator Yaw and make sure the length is 1
		FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		
		AddMovementInput(Direction, Value * CurrentSpeed);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if(!bIsPickingUp && Controller != nullptr && Value != 0)
	{
		// Get the Rotation of the Controller as this may not be the same as the camera
		FRotator Rotation = Controller->GetControlRotation();
		// We only want the Yaw part
		FRotator Yaw = FRotator(0, Rotation.Yaw, 0);
		// Get the right vector of the Rotator Yaw and make sure the length is 1
		FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Direction, Value * CurrentSpeed);
	}
}

void APlayerCharacter::HorizontalRotation(float Value)
{
	if(Value)
	{
		AddControllerYawInput(Value * GetWorld()->GetDeltaSeconds() * TurnRate);
	}
}

void APlayerCharacter::VerticalRotation(float Value)
{
	if(Value)
	{
		AddControllerPitchInput(Value * -1 * GetWorld()->GetDeltaSeconds() * LookUpRate);
	}
}

void APlayerCharacter::Zoom(float Value)
{
	if(Value)
	{
		float FinalZoomLength = SpringArmComponent->TargetArmLength + (Value * -10);
		// Avoid infinite Zoom
		if(FinalZoomLength < ZoomOutMax && FinalZoomLength > ZoomInMax)
		{
			SpringArmComponent->TargetArmLength = FinalZoomLength;
		}
	}
}

AFood* APlayerCharacter::DropFood()
{
	bIsCarrying = false;
	CurrentSpeed = DefaultSpeed;
	CarryFood->Drop();
	return CarryFood;
}

void APlayerCharacter::HasWon()
{
	bHasWon = true;
	StopMovement();
}

void APlayerCharacter::HasLost()
{
	bHasLost = true;
	StopMovement();
}

bool APlayerCharacter::GetHasWon()
{
	return bHasWon;
}

bool APlayerCharacter::GetHasLost()
{
	return bHasLost;
}

bool APlayerCharacter::GetIsCarrying()
{
	return bIsCarrying;
}

void APlayerCharacter::StopMovement()
{
	if(bIsCarrying)
	{
		DropFood();
	}
	DisableInput(GetWorld()->GetFirstPlayerController());
}

void APlayerCharacter::Interact()
{
	if(bCanPickUp || bIsCarrying)
	{
		if(bIsCarrying)
		{
			DropFood();
		} else
		{
			bIsCarrying = true;
			bIsPickingUp = true;
			CurrentSpeed = DefaultSpeed / 2.f;
			if(InCollisionFood != nullptr)
			{
				CarryFood = InCollisionFood;

				GetMesh()->PlayAnimation(PickUpAnimationSequence, false);
				GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayerCharacter::TimerPickUpAnim, PickUpAnimationSequence->SequenceLength, false);
			}
		}
	}
}

void APlayerCharacter::TimerPickUpAnim()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CarryFood->PickUp(HoldingComponent);
	bIsPickingUp = false;
}

void APlayerCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AFood::StaticClass())){
		InCollisionFood = Cast<AFood>(OtherActor);
		bCanPickUp = true;
	}
}

void APlayerCharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->IsA(AFood::StaticClass())){
		bCanPickUp = false;
		InCollisionFood = nullptr;
	}
}

void APlayerCharacter::PauseGame()
{
	Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->ShowPauseScreen();
}
