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
	TimerDelay = 0.01f;
	bIsSnakeGrowing = false;
	bCanSpawn = true;
	OneTimeSpawnAmount = 1;
}

void AMySnakeController::BeginPlay()
{
	Super::BeginPlay();

	MySnakePawn = Cast<AMySnakePawn>(GetPawn());
	GMRef = Cast<AMySnakeGameMode>(GetWorld()->GetAuthGameMode());
	class ALevelProps* Props = Cast<ALevelProps>(GetPawn());

	if (Props)
	{
		SetViewTarget(Props);
	}

	MovementDirection = FVector::ZeroVector;
	GetWorld()->GetTimerManager().SetTimer(MovementLoopTimerHandle, this, &AMySnakeController::GridMove,TimerDelay,true);

	MyActorsArr.Add(MySnakePawn);
}

void AMySnakeController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//GridMove();
}

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
	//class AMySnakePawn* MyPawn = Cast<AMySnakePawn>(GetPawn());

	FVector Temp = MovementDirection;

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

		if (Temp == -MovementDirection && bIsSnakeGrowing)
		{
			UE_LOG(LogTemp, Error, TEXT("Wrong Button!!!"));
			MovementDirection = Temp;
		}
	}
	
}

void AMySnakeController::GridMove()
{
	FVector CurrentPosition = FVector(MyActorsArr[0]->GetActorLocation().X, MyActorsArr[0]->GetActorLocation().Y, 50.f);

	MyActorsArr[0]->SetActorLocation(CurrentPosition + MovementDirection, true);

	/*for (int i = 1; i < MyActorsArr.Num(); i++)
	{
		FVector PreviousPosition = MyActorsArr[i]->GetActorLocation();
		MyActorsArr[i]->SetActorLocation(CurrentPosition,true);
		CurrentPosition = PreviousPosition;
	}*/

	if (bIsSnakeGrowing)
	{
		for (int32 i = MyActorsArr.Num() - 1 ; i > 0; i--)
		{
			FVector PreviousPosition = MyActorsArr[i]->GetActorLocation();
			MyActorsArr[i]->SetActorLocation(CurrentPosition, true);
			CurrentPosition = PreviousPosition;
		}
	}
}

void AMySnakeController::RestartLevel()
{
	if (GMRef->GetbIsGameOver())
	{
		Super::RestartLevel();
	}
}

FVector AMySnakeController::GetMovementDirection() const
{
	return MovementDirection;
}

void AMySnakeController::StopMyTimer() const
{
	GetWorldTimerManager().ClearTimer(MovementLoopTimerHandle);
}

void AMySnakeController::SpawnSnakeParts()
{
	if (ItemToSpawn != NULL)
	{
		UWorld* const World = GetWorld();

		if (World)
		{
			for (int i = 0; i < OneTimeSpawnAmount; i++)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Last member of array: %s and actor location is %s "), *MyActorsArr.Last()->GetName(), *MyActorsArr.Last()->GetActorLocation().ToString());
				//FVector SpawnLocation = MyActorsArr.Last()->GetActorLocation() - MovementDirection;
				FVector SpawnLocation = (MyActorsArr[0]->GetActorLocation() - MovementDirection);
				AMySpawnActor* const SnakePart = World->SpawnActor<AMySpawnActor>(ItemToSpawn, SpawnLocation, FRotator::ZeroRotator);
				MyActorsArr.Add(SnakePart);
			}

		}
	}
}
