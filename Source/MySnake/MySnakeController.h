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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer")
	float TimerDelay;

	UFUNCTION()
	FVector GetMovementDirection() const;

protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void ChangeMoveDirection();
	void GridMove();

private:

	UPROPERTY()
	class AMySnakePawn* MySnakePawn;

	UPROPERTY()
	FVector MovementDirection;

	FTimerHandle MovementLoopTimerHandle;
	
	
};
