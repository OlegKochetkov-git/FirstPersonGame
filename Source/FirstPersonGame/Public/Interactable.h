// First Person Game

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class FIRSTPERSONGAME_API IInteractable
{
	GENERATED_BODY()

public:
	virtual void DoSomething() = 0;
};
