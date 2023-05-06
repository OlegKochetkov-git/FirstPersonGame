// First Person Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/FPBaseCharacter.h"
#include "FPInputHandlerComponent.generated.h"

struct FInputActionValue;
class UFPInputHandlerComponent;
class UInputAction;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONGAME_API UFPInputHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFPInputHandlerComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Context")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Action")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input Action")
	UInputAction* LookAction;
	
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:	
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

private:
	UPROPERTY()
	AController* CurrentController = nullptr;
	UPROPERTY()
	APawn* CurrentPawn = nullptr;
	
	AController* GetController();
	APawn* GetPawn();
	
	void Checking() const;
	void AddDefaultMappingContext();
};