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

	Score = 0;
}

void AMySnakeGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnFood();
}

void AMySnakeGameMode::SpawnFood()
{
	if (ItemToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		LevelRef = ALevelProps::StaticClass();

		if (World)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawn FOOD from GM"));
			//FVector SpawnLocation = GetRandomPointsInVolume();
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
			
			//UE_LOG(LogTemp, Warning, TEXT("SPAWN THE FUCK!!!!"));

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


