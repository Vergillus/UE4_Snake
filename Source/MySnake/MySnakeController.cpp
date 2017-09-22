// Fill out your copyright notice in the Description page of Project Settings.

#include "MySnakeController.h"
#include "MySnakePawn.h"
#include "Components/BoxComponent.h"
#include "LevelProps.h"
#include "Engine/World.h"

AMySnakeController::AMySnakeController()
{
	TimerDelay = 0.01f;
}

void AMySnakeController::BeginPlay()
{
	Super::BeginPlay();

	MySnakePawn = Cast<AMySnakePawn>(GetPawn());

	class ALevelProps* Props = Cast<ALevelProps>(GetPawn());

	if (Props)
	{
		SetViewTarget(Props);
	}

	MovementDirection = FVector::ZeroVector;
	GetWorld()->GetTimerManager().SetTimer(MovementLoopTimerHandle, this, &AMySnakeController::GridMove,TimerDelay,true);
}

void AMySnakeController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);	
}

void AMySnakeController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction("ChangeDirection", IE_Pressed, this, &AMySnakeController::ChangeMoveDirection);
	//InputComponent->BindAxis("MoveForward",this,&AMySnakeController::MoveForward);
	
}

void AMySnakeController::ChangeMoveDirection()
{
	//class AMySnakePawn* MyPawn = Cast<AMySnakePawn>(GetPawn());

	if (MySnakePawn)
	{
		if (IsInputKeyDown(EKeys::Up))
		{
			MovementDirection = FVector(100.f, 0.f, 0.f);
		}
		//MySnakePawn->SetActorLocation(FVector(100, 100, 0));
		if (IsInputKeyDown(EKeys::Down))
		{
			MovementDirection = FVector(-100.f, 0.f, 0.f);
		}

		if (IsInputKeyDown(EKeys::Left))
		{
			MovementDirection = FVector(0.f, -100.f, 0.f);
		}

		if (IsInputKeyDown(EKeys::Right))
		{
			MovementDirection = FVector(0.f, +100.f, 0.f);
		}

		/*UBoxComponent* Box = MyPawn->GetCollisionComponent();
		Box->SetWorldLocation(FVector(100, 100, 0));*/
	}
}

void AMySnakeController::GridMove()
{
	FVector CurrentPosition = FVector(MySnakePawn->GetActorLocation().X, MySnakePawn->GetActorLocation().Y, 55.f);

	MySnakePawn->SetActorLocation(CurrentPosition + MovementDirection,true);	
}

FVector AMySnakeController::GetMovementDirection() const
{
	return MovementDirection;
}
