// Fill out your copyright notice in the Description page of Project Settings.

#include "MySnakeController.h"
#include "MySnakePawn.h"
#include "Components/BoxComponent.h"
#include "LevelProps.h"
#include "Engine/World.h"
#include "MySpawnActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

AMySnakeController::AMySnakeController()
{
	TimerDelay = 0.01f;
	bIsSnakeGrowing = false;
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

	MyActorsArr.Add(MySnakePawn);

	/*static ConstructorHelpers::FObjectFinder<UMaterial> Mat(TEXT("MaterialInstanceConstant'/Game/Materials/Green_Inst.Green_Inst''"));

	if (Mat.Succeeded())
	{
		SnakeMat = (UMaterial*)Mat.Object;
	}*/

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

	FVector Temp = MovementDirection;

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

		if (Temp == -MovementDirection && bIsSnakeGrowing)
		{
			UE_LOG(LogTemp, Error, TEXT("Wrong Button!!!"));
			MovementDirection = Temp;
		}


		/*UBoxComponent* Box = MyPawn->GetCollisionComponent();
		Box->SetWorldLocation(FVector(100, 100, 0));*/
	}
}

void AMySnakeController::GridMove()
{
	FVector CurrentPosition = FVector(MySnakePawn->GetActorLocation().X, MySnakePawn->GetActorLocation().Y, 55.f);

	MySnakePawn->SetActorLocation(CurrentPosition + MovementDirection, true);

	for (int i = 1; i < MyActorsArr.Num(); i++)
	{
		FVector Temp = MyActorsArr[i]->GetActorLocation();
		MyActorsArr[i]->SetActorLocation(CurrentPosition,true);
		CurrentPosition = Temp;
	}

	
}

FVector AMySnakeController::GetMovementDirection() const
{
	return MovementDirection;
}


void AMySnakeController::SpawnSnakeParts()
{
	if (ItemToSpawn != NULL)
	{
		UWorld* const World = GetWorld();

		if (World)
		{
			for (int i = 0; i < 5; i++)
			{
				UE_LOG(LogTemp, Warning, TEXT("Last member of array: %s and actor location is %s "), *MyActorsArr.Last()->GetName(), *MyActorsArr.Last()->GetActorLocation().ToString());
				FVector SpawnLocation = MyActorsArr.Last()->GetActorLocation() - MovementDirection;
				AMySpawnActor* const SnakePart = World->SpawnActor<AMySpawnActor>(ItemToSpawn, SpawnLocation, FRotator::ZeroRotator);
				MyActorsArr.Add(SnakePart);
				//UE_LOG(LogTemp, Warning, TEXT("SPAWN THE FUCK!!!!"));

			}

		}
	}
}
