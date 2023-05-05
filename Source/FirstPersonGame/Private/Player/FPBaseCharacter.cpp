// First Person Game

#include "Player/FPBaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

AFPBaseCharacter::AFPBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(RootComponent);
}

void AFPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Checking();
	AddDefaultMappingContext();
}

void AFPBaseCharacter::Checking() const
{
	checkf(CameraComponent, TEXT("Pointer CameraComponent is nullptr in class %s,"), *StaticClass()->GetName());
	checkf(MovementAction, TEXT("Pointer MoveAction is nullptr in class %s,"), *StaticClass()->GetName());
	checkf(PlayerMappingContext, TEXT("Pointer PlayerMappingContext is nullptr in class %s"), *StaticClass()->GetName());
}

void AFPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AFPBaseCharacter::Move);
	}
}

void AFPBaseCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	const FVector Forward = GetActorForwardVector();
	const FVector Right = GetActorRightVector();

	AddMovementInput(Forward, DirectionValue.Y);
	AddMovementInput(Right, DirectionValue.X);
}

void AFPBaseCharacter::AddDefaultMappingContext()
{
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}