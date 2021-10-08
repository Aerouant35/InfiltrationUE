// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &AMyCharacter::HorizontalMove);
	InputComponent->BindAxis("Vertical", this, &AMyCharacter::VerticalMove);

	InputComponent->BindAxis("Zoom", this, &AMyCharacter::Zoom);
	
	InputComponent->BindAxis("HorizontalRotation", this, &AMyCharacter::HorizontalRotation);
	InputComponent->BindAxis("VerticalRotation", this, &AMyCharacter::VerticalRotation);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);

}

void AMyCharacter::HorizontalMove(float Value)
{
	if(Value)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyCharacter::VerticalMove(float Value)
{
	if(Value)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyCharacter::HorizontalRotation(float Value)
{
	if(Value)
	{
		AddActorLocalRotation(FRotator(0, Value, 0));
	}
}

void AMyCharacter::VerticalRotation(float Value)
{
	if(Value)
	{
		float FinalRotation = SpringArmComponent->GetRelativeRotation().Pitch + Value;
		// Avoid rotate at weird angles
		if(FinalRotation < 25 && FinalRotation > -65)
		{
			SpringArmComponent->AddLocalRotation(FRotator(Value, 0, 0));
		}
	}
}

void AMyCharacter::Zoom(float Value)
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

void AMyCharacter::Interact()
{
	// TODO
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Pressed the Interact Key !"));
}

