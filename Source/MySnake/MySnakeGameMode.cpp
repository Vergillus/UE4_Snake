// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MySnakeGameMode.h"
#include "MySnakePlayerController.h"
#include "MySnakeCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "LevelProps.h"
#include "Components/BoxComponent.h"
#include "MySpawnActor.h"

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

	// Set defaults
	Score = 0;
	bIsGameOver = false;
}

void AMySnakeGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnFood();
}
// Spawns the food
void AMySnakeGameMode::SpawnFood()
{
	if (ItemToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		LevelRef = ALevelProps::StaticClass();

		if (World)
		{			
			if (LevelRef)
			{
				FVector SpawnLocation = LevelRef.GetDefaultObject()->GetRandomPointsInVolume();
				UBoxComponent* SpawnComp = LevelRef.GetDefaultObject()->GetSpawningVolume();
				if (SpawnComp)
				{
					SpawnLocation.Z = SpawnComp->GetRelativeTransform().GetLocation().Z;
					World->SpawnActor<AMySpawnActor>(ItemToSpawn, SpawnLocation, FRotator::ZeroRotator);
				}
			}			
			
		}
	}
}

void AMySnakeGameMode::IncrementScore()
{
	Score = Score + 1;
}

int AMySnakeGameMode::GetScore() const
{
	return Score;
}

bool AMySnakeGameMode::GetbIsGameOver() const
{
	return bIsGameOver;
}

void AMySnakeGameMode::SetbIsGameOver(bool val)
{
	bIsGameOver = val;
}


