// First Person Game

#include "Player/FPBaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

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
	CameraComponent->bUsePawnControlRotation = true;
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
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPBaseCharacter::Look);
	}
}

void AFPBaseCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	UE_LOG(LogBaseCharacter, Warning, TEXT("Forward %s"), *ForwardDirection.ToString());
	UE_LOG(LogBaseCharacter, Warning, TEXT("Right %s"), *RightDirection.ToString());
	
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AFPBaseCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
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
