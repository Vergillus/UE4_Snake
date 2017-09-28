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
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class ALevelProps> LevelRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class AMySpawnActor> ItemToSpawn;

	UFUNCTION()
	void IncrementScore();

	UFUNCTION()
	int GetScore() const;

	UFUNCTION()
	bool GetbIsGameOver() const;

	UFUNCTION()
	void SetbIsGameOver();

	UFUNCTION()
	void SpawnFood();

private:

	UPROPERTY()
	int Score;

	UPROPERTY()
	bool bIsGameOver;

};



