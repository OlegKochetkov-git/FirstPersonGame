// First Person Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPBaseCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class FIRSTPERSONGAME_API AFPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPBaseCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	void Move(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Checking() const;
	void AddDefaultMappingContext();
};
