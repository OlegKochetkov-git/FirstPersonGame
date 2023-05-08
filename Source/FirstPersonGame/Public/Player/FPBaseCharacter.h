// First Person Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPBaseCharacter.generated.h"

struct FInputActionValue;
class UFPInputHandlerComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class FIRSTPERSONGAME_API AFPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPBaseCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UFPInputHandlerComponent* InputHandlerComponent;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Checking() const;
	void CreateObjects();
};
