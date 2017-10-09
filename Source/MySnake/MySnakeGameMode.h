// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MySnakeGameMode.generated.h"

UCLASS(minimalapi)
class AMySnakeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMySnakeGameMode();	

	virtual void BeginPlay() override;

	// A pointer referance to ALevelProps class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class ALevelProps> LevelRef;

	// Food to spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class AMySpawnActor> ItemToSpawn;

	// Increase the score with each consumed food
	UFUNCTION()
	void IncrementScore();
	// Return the score
	UFUNCTION()
	int GetScore() const;

	// Return bIsGameOver bool variable
	UFUNCTION()
	bool GetbIsGameOver() const;

	// Set bIsGameOver bool variable
	UFUNCTION()
	void SetbIsGameOver(bool val);

	// Spawn the food
	UFUNCTION()
	void SpawnFood();

private:

	// Variable to store score;
	UPROPERTY()
	int Score;

	// Flag that indicates the game is over or not
	UPROPERTY()
	bool bIsGameOver;

};



