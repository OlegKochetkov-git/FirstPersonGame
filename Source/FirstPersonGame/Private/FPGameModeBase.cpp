// First Person Game

#include "FPGameModeBase.h"
#include "FPBaseCharacter.h"
#include "FPPlayerController.h"

AFPGameModeBase::AFPGameModeBase()
{
	DefaultPawnClass = AFPBaseCharacter::StaticClass();
	PlayerControllerClass = AFPPlayerController::StaticClass();
}
