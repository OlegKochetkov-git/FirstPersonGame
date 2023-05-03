// First Person Game

#include "Player/FPBaseCharacter.h"

AFPBaseCharacter::AFPBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}