// First Person Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPBaseCharacter.generated.h"

UCLASS()
class FIRSTPERSONGAME_API AFPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
