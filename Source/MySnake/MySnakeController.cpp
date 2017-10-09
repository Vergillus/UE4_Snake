// Fill out your copyright notice in the Description page of Project Settings.

#include "MySnakeController.h"
#include "MySnakePawn.h"
#include "Components/BoxComponent.h"
#include "LevelProps.h"
#include "Engine/World.h"
#include "MySpawnActor.h"
#include "MySnakeGameMode.h"

AMySnakeController::AMySnakeController()
{
	// Setup Defaults
	TimerDelay = 0.01f;	
	OneTimeSpawnAmount = 1;
}

void AMySnakeController::BeginPlay()
{
	Super::BeginPlay();
	// Point to MySnakePawn Class
	MySnakePawn = Cast<AMySnakePawn>(GetPawn());
	// Point to GameMode class
	GMRef = Cast<AMySnakeGameMode>(GetWorld()->GetAuthGameMode());
	
	MovementDirection = FVector::ZeroVector;

	//Start timer that calls GridMove function in ever given interval
	GetWorld()->GetTimerManager().SetTimer(MovementLoopTimerHandle, this, &AMySnakeController::GridMove,TimerDelay,true);

	// Populate the array with MySnakePawn as first item
	MyActorsArr.Add(MySnakePawn);
}

void AMySnakeController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}
// Called to bind functionality to input
void AMySnakeController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAction("ChangeDirection", IE_Pressed, this, &AMySnakeController::ChangeMoveDirection);
	InputComponent->BindAction("Restart", IE_Pressed, this, &AMySnakeController::RestartLevel);
	//InputComponent->BindAxis("MoveForward",this,&AMySnakeController::MoveForward);
	
}

void AMySnakeController::ChangeMoveDirection()
{
	// Store MovementDirection before changing it
	FVector Temp = MovementDirection;
	
	// Change the MovementDirection according to key press
	if (MySnakePawn && !GMRef->GetbIsGameOver())
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

		// Constraint Movement when there are more than one snake parts to avoid moving back
		if (Temp == -MovementDirection && MyActorsArr.Num() > 1)
		{	
			MovementDirection = Temp;
		}
	}
	
}
// Implements grid move 
void AMySnakeController::GridMove()
{
	// Get the current position of first item in the array
	FVector CurrentPosition = FVector(MyActorsArr[0]->GetActorLocation().X, MyActorsArr[0]->GetActorLocation().Y, 50.f);

	// Set the first item location in the array
	MyActorsArr[0]->SetActorLocation(CurrentPosition + MovementDirection, true);

	/*for (int i = 1; i < MyActorsArr.Num(); i++)
	{
		FVector PreviousPosition = MyActorsArr[i]->GetActorLocation();
		MyActorsArr[i]->SetActorLocation(CurrentPosition,true);
		CurrentPosition = PreviousPosition;
	}*/

	// IF the array size is bigger than 1 start shifting each array element to the position of previous element in reverse order.
	if (MyActorsArr.Num() > 1)
	{
		for (int32 i = MyActorsArr.Num() - 1 ; i > 0; i--)
		{
			FVector PreviousPosition = MyActorsArr[i]->GetActorLocation();
			MyActorsArr[i]->SetActorLocation(CurrentPosition, true);
			CurrentPosition = PreviousPosition;
		}
	}
}
// Overided Restart Level fuction
void AMySnakeController::RestartLevel()
{
	if (GMRef->GetbIsGameOver())
	{
		Super::RestartLevel();
	}
}
// Retunr Current Movemement vector
FVector AMySnakeController::GetMovementDirection() const
{
	return MovementDirection;
}
// Stops World Timer
void AMySnakeController::StopMyTimer() const
{
	GetWorldTimerManager().ClearTimer(MovementLoopTimerHandle);
}
// Spawns snake parts
void AMySnakeController::SpawnSnakeParts()
{
	if (ItemToSpawn != NULL)
	{
		UWorld* const World = GetWorld();

		if (World)
		{
			// Spawn snake parts at back of the head always
			for (int i = 0; i < OneTimeSpawnAmount; i++)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Last member of array: %s and actor location is %s "), *MyActorsArr.Last()->GetName(), *MyActorsArr.Last()->GetActorLocation().ToString());
				//FVector SpawnLocation = MyActorsArr.Last()->GetActorLocation() - MovementDirection;
				FVector SpawnLocation = (MyActorsArr[0]->GetActorLocation() - MovementDirection);
				AMySpawnActor* const SnakePart = World->SpawnActor<AMySpawnActor>(ItemToSpawn, SpawnLocation, FRotator::ZeroRotator);
				// Add the spawned parts to array
				MyActorsArr.Add(SnakePart);
			}

		}
	}
}
