// First Person Game

#include "Player/FPBaseCharacter.h"
#include "Player/Components/FPInputHandlerComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

AFPBaseCharacter::AFPBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CreateObjects();
}

void AFPBaseCharacter::CreateObjects()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;
	
	InputHandlerComponent = CreateDefaultSubobject<UFPInputHandlerComponent>("InputHandlerComponent");
}

void AFPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Checking();
}

void AFPBaseCharacter::Checking() const
{
	checkf(CameraComponent, TEXT("Pointer CameraComponent is nullptr in class %s,"), *StaticClass()->GetName());
	checkf(InputHandlerComponent, TEXT("Pointer InputHandlerComponent is nullptr in class %s,"), *StaticClass()->GetName());
}

void AFPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AFPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputHandlerComponent->SetupPlayerInputComponent(PlayerInputComponent);
}
