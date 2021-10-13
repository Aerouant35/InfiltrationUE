// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	HoldingComp = CreateDefaultSubobject<USceneComponent>("HoldingComponent");
	HoldingComp->SetRelativeLocation(FVector(50.f, HoldingComp->GetRelativeLocation().Y, HoldingComp->GetRelativeLocation().Z));
	HoldingComp->SetupAttachment(GetCapsuleComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	
	TurnRate = 45.f;
	LookUpRate = 45.f;
	Speed = 1.f;

	bIsCarrying = false;
	bIsPickingUp = false;
	bCanPickUp = false;

	InCollisionFood = nullptr;
	CarryFood = nullptr;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnComponentEndOverlap);
	
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
		
		AddMovementInput(Direction, Value * Speed);
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
		
		AddMovementInput(Direction, Value * Speed);
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

void APlayerCharacter::Interact()
{
	if(bCanPickUp || bIsCarrying)
	{
		if(bIsCarrying)
		{
			bIsCarrying = false;
			Speed = 1.f;
			CarryFood->PickUp();
		} else
		{
			bIsCarrying = true;
			bIsPickingUp = true;
			Speed = 0.5f;
			if(InCollisionFood != nullptr)
			{
				CarryFood = InCollisionFood;

				GetMesh()->PlayAnimation(AnimationAsset, false);
				GetWorldTimerManager().SetTimer(UnusedHandle, this, &APlayerCharacter::TimerPickUpAnim, 1.25, false);
			}
		}
	}
}

void APlayerCharacter::TimerPickUpAnim()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CarryFood->PickUp();
	bIsPickingUp = false;
}

void APlayerCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		InCollisionFood = Cast<AFood>(OtherActor);
		bCanPickUp = true;
	}
}

void APlayerCharacter::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->GetClass()->IsChildOf(AFood::StaticClass())){
		bCanPickUp = false;
		InCollisionFood = nullptr;
	}
}


