// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/CharactKnight.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Level/GameHUD.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

// Sets default values
ACharactKnight::ACharactKnight()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
void ACharactKnight::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACharactKnight::OnComponentBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACharactKnight::OnComponentEndOverlap);

	GetCharacterMovement()->RotationRate = RotationRate;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called to bind functionality to input
void ACharactKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharactKnight::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharactKnight::MoveRight);

	PlayerInputComponent->BindAxis("Zoom", this, &ACharactKnight::Zoom);
	
	PlayerInputComponent->BindAxis("HorizontalRotation", this, &ACharactKnight::HorizontalRotation);
	PlayerInputComponent->BindAxis("VerticalRotation", this, &ACharactKnight::VerticalRotation);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharactKnight::Interact);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ACharactKnight::PauseGame);

}

#pragma region Delegate Methods
void ACharactKnight::MoveForward(const float Value)
{
	if(!bIsPickingUp && Controller != nullptr && Value != 0)
	{
		// Get the Rotation of the Controller as this may not be the same as the camera
		const FRotator Rotation = Controller->GetControlRotation();
		// We only want the Yaw part
		const FRotator Yaw = FRotator(0, Rotation.Yaw, 0);
		// Get the forward vector of the Rotator Yaw and make sure the length is 1
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		
		AddMovementInput(Direction, Value * CurrentSpeed);
	}
}

void ACharactKnight::MoveRight(const float Value)
{
	if(!bIsPickingUp && Controller != nullptr && Value != 0)
	{
		// Get the Rotation of the Controller as this may not be the same as the camera
		const FRotator Rotation = Controller->GetControlRotation();
		// We only want the Yaw part
		const FRotator Yaw = FRotator(0, Rotation.Yaw, 0);
		// Get the right vector of the Rotator Yaw and make sure the length is 1
		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Direction, Value * CurrentSpeed);
	}
}

void ACharactKnight::HorizontalRotation(const float Value)
{
	if(!Value) return;

	AddControllerYawInput(Value * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void ACharactKnight::VerticalRotation(const float Value)
{
	if(!Value) return;
	
	AddControllerPitchInput(Value * -1 * GetWorld()->GetDeltaSeconds() * LookUpRate);
}

void ACharactKnight::Zoom(const float Value)
{
	if(!Value) return;
	
	const float FinalZoomLength = SpringArmComponent->TargetArmLength + Value * ZoomStep;
	
	// Avoid infinite Zoom
	if(FinalZoomLength < ZoomOutMax && FinalZoomLength > ZoomInMax)
	{
		SpringArmComponent->TargetArmLength = FinalZoomLength;
	}
}

void ACharactKnight::Interact()
{
	if(bIsCarrying)
	{
		DropFood();
	}
	else if (bCanPickUp)
	{	
		bIsCarrying = true;
		bIsPickingUp = true;
		CurrentSpeed = DefaultSpeed / 2.f;

		check(InCollisionFood != nullptr);

		CarryFood = InCollisionFood;

		GetMesh()->PlayAnimation(PickUpAnimationSequence, false);
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ACharactKnight::TimerPickUpAnim, PickUpAnimationSequence->SequenceLength, false);
	}
}

void ACharactKnight::PauseGame()
{
	if (GameHUD == nullptr)
	{
		GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		check(GameHUD != nullptr);
	}
	else
		GameHUD->ShowPauseScreen();
}
#pragma endregion

#pragma region Overlap Methods
void ACharactKnight::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AFood::StaticClass())){
		InCollisionFood = Cast<AFood>(OtherActor);
		bCanPickUp = true;
	}
}

void ACharactKnight::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->IsA(AFood::StaticClass())){
		bCanPickUp = false;
		InCollisionFood = nullptr;
	}
}
#pragma endregion

#pragma region ProtectedMethod
void ACharactKnight::TimerPickUpAnim()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	CarryFood->PickUp(HoldingComponent);
	bIsPickingUp = false;
}

void ACharactKnight::StopMovement()
{
	if(bIsCarrying)
	{
		DropFood();
	}
	
	DisableInput(GetWorld()->GetFirstPlayerController());
}
#pragma endregion

#pragma region PublicMethod
AFood* ACharactKnight::DropFood()
{
	check(CarryFood != nullptr);
	
	bIsCarrying = false;
	CurrentSpeed = DefaultSpeed;
	CarryFood->Drop();
	return CarryFood;
}

void ACharactKnight::HasWon()
{
	bHasWon = true;
	StopMovement();
}

void ACharactKnight::HasLost()
{
	bHasLost = true;
	StopMovement();
}
#pragma endregion 
