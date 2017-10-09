// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MySnakeController.generated.h"

/**
 * 
 */
UCLASS()
class MYSNAKE_API AMySnakeController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMySnakeController();

	// Constant tick time for timer
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer")
	float TimerDelay;

	// Returns direction vector 
	UFUNCTION()
	FVector GetMovementDirection() const;

	// Item that is going to be spawned
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class AMySpawnActor> ItemToSpawn;

	// Function that creates snake parts
	UFUNCTION()
	void SpawnSnakeParts();

	// An int variable to constraint the number of spawn snake parts at a time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawnin")
	int OneTimeSpawnAmount;

	// Fuction that stops the timer
	UFUNCTION()
	void StopMyTimer() const;
	
protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void RestartLevel() override;

	// Changes the direction of Snake
	void ChangeMoveDirection();
	// Implements grid move 
	void GridMove();

private:

	// Pointer referance of MySnakePawn
	UPROPERTY()
	class AMySnakePawn* MySnakePawn;

	// Pointer referance of MySnakeGameMode
	UPROPERTY()
	class AMySnakeGameMode* GMRef;

	// A vector to hold movement direction
	UPROPERTY()
	FVector MovementDirection;
		
	UPROPERTY()
	FTimerHandle MovementLoopTimerHandle;

	UPROPERTY()
	TArray<AActor*> MyActorsArr;	

};
