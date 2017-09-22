// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MySnakeGameMode.h"
#include "MySnakePlayerController.h"
#include "MySnakeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMySnakeGameMode::AMySnakeGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMySnakePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
