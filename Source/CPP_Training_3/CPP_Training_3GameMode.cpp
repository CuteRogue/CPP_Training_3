// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP_Training_3GameMode.h"
#include "CPP_Training_3Character.h"
#include "UObject/ConstructorHelpers.h"

ACPP_Training_3GameMode::ACPP_Training_3GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
