// First Person Game

#include "Player/Components/FPInputHandlerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

UFPInputHandlerComponent::UFPInputHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFPInputHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	Checking();
	AddDefaultMappingContext();
}

void UFPInputHandlerComponent::Checking() const
{
	checkf(PlayerMappingContext, TEXT("Pointer PlayerMappingContext is nullptr in class %s"), *StaticClass()->GetName());
	checkf(MovementAction, TEXT("Pointer MoveAction is nullptr in class %s,"), *StaticClass()->GetName());
	checkf(LookAction, TEXT("Pointer LookAction is nullptr in class %s,"), *StaticClass()->GetName());
}

void UFPInputHandlerComponent::AddDefaultMappingContext()
{
	if (const APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

void UFPInputHandlerComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &UFPInputHandlerComponent::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UFPInputHandlerComponent::Look);
	}
}

void UFPInputHandlerComponent::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (!GetController()) return;
	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void UFPInputHandlerComponent::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	GetPawn()->AddControllerPitchInput(LookAxisVector.Y);
	GetPawn()->AddControllerYawInput(LookAxisVector.X);
}

AController* UFPInputHandlerComponent::GetController()
{
	if (CurrentController) return CurrentController;
	
	if (!GetPawn()) return nullptr;
	CurrentController = GetPawn()->GetController();
	return CurrentController;
}

APawn* UFPInputHandlerComponent::GetPawn()
{
	if (CurrentPawn) return CurrentPawn;
	
	CurrentPawn = Cast<APawn>(GetOwner());
	return CurrentPawn;
}
