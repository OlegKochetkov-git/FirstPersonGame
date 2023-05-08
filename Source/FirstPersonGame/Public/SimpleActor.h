// First Person Game

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "SimpleActor.generated.h"

UCLASS()
class FIRSTPERSONGAME_API ASimpleActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ASimpleActor();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	virtual void BeginPlay() override;

public:	
	virtual void DoSomething() override;
};
