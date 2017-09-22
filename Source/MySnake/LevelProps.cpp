// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelProps.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "MySpawnActor.h"



// Sets default values
ALevelProps::ALevelProps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorOBJ(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (FloorOBJ.Succeeded())
	{
		Floor->SetStaticMesh(FloorOBJ.Object);
	}

	Floor->RelativeScale3D = FVector(15.f, 15.f, 1.f);
	Floor->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	Floor->bGenerateOverlapEvents = false;
	RootComponent = Floor;

	SpawningVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));
	SpawningVolume->SetBoxExtent(FVector(Floor->Bounds.BoxExtent.X, Floor->Bounds.BoxExtent.Y, 32.f));
	SpawningVolume->SetupAttachment(RootComponent);
	SpawningVolume->SetRelativeLocation(FVector(0.f, 0.f, SpawningVolume->Bounds.BoxExtent.Z));
	SpawningVolume->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	SpawningVolume->bGenerateOverlapEvents = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->RelativeRotation = FRotator(-90.f, 0.f, 0.f);

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	TopDownCamera->OrthoWidth = 1500.f;
	TopDownCamera->bConstrainAspectRatio = true;
	TopDownCamera->AspectRatio = 1.f;
	TopDownCamera->SetAbsolute(false, false, true);	

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_OBJ(TEXT("Blueprint'/Game/Blueprints/BP_SpawnActorFood.BP_SpawnActorFood'"));
	if (BP_OBJ.Succeeded())
	{
		ItemToSpawn = (UClass*)BP_OBJ.Object->GeneratedClass;
	}

}

// Called when the game starts or when spawned
void ALevelProps::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerCont = GetWorld()->GetFirstPlayerController();

	if (PlayerCont)
	{
		PlayerCont->SetViewTarget(this);
	}
	
	SpawnMyActor();
}

// Called every frame
void ALevelProps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ALevelProps::GetRandomPointsInVolume()
{
	FVector BoxExtent = SpawningVolume->Bounds.BoxExtent;
	FVector Origin = SpawningVolume->Bounds.Origin;
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);

	return RoundToMultiple(RandomPoint, 100);
}

FVector ALevelProps::RoundToMultiple(const FVector VectorToRound, const int32 Multiple)
{
	/*check(Multiple);
	int32 IsPositive = (int)(VectorToRound.X >= 0 && VectorToRound.Y >= 0);
	FVector NewVector;
	NewVector.X = ((VectorToRound.X + IsPositive * (Multiple - 1)) / Multiple) * Multiple;
	NewVector.Y = ((VectorToRound.Y + IsPositive * (Multiple - 1)) / Multiple) * Multiple;

	return NewVector;*/

	if (Multiple == 0)
	{
		return VectorToRound;
	}

	int RemainderX = (int)VectorToRound.X % Multiple;
	int RemainderY = (int)VectorToRound.Y % Multiple;

	if (RemainderX == 0 || RemainderY == 0)
	{
		return VectorToRound;
	}

	FVector NewVec;
	NewVec.X = VectorToRound.X + Multiple - RemainderX;
	NewVec.Y = VectorToRound.Y + Multiple - RemainderY;

	if (NewVec.X > SpawningVolume->Bounds.BoxExtent.X)
	{
		NewVec.X -= Multiple;
	}
	if (NewVec.Y > SpawningVolume->Bounds.BoxExtent.Y)
	{
		NewVec.Y -= Multiple;
	}

	/*FMath::Clamp(NewVec.X, 0.f, SpawningVolume->Bounds.BoxExtent.X);
	FMath::Clamp(NewVec.Y, 0.f, SpawningVolume->Bounds.BoxExtent.Y);*/

	return NewVec;
}

void ALevelProps::SpawnMyActor()
{
	if (ItemToSpawn != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn FOOD"));
		UWorld* const World = GetWorld();

		if (World)
		{
			FVector SpawnLocation = GetRandomPointsInVolume();
			SpawnLocation.Z = SpawningVolume->GetRelativeTransform().GetLocation().Z;
			World->SpawnActor<AMySpawnActor>(ItemToSpawn, SpawnLocation, FRotator::ZeroRotator);
			//UE_LOG(LogTemp, Warning, TEXT("SPAWN THE FUCK!!!!"));

		}
	}
}

