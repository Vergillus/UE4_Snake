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

	// Create and setup default values for Floor component
	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorOBJ(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
	if (FloorOBJ.Succeeded())
	{
		Floor->SetStaticMesh(FloorOBJ.Object);
	}

	Floor->RelativeScale3D = FVector(15.f, 15.f, 1.f);
	Floor->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	Floor->bGenerateOverlapEvents = false;
	// Set floor as root component
	RootComponent = Floor;

	// Create and setup default values for SpawningVolume component
	SpawningVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));
	SpawningVolume->SetBoxExtent(FVector(Floor->Bounds.BoxExtent.X, Floor->Bounds.BoxExtent.Y, 32.f));
	SpawningVolume->SetupAttachment(RootComponent);
	SpawningVolume->SetRelativeLocation(FVector(0.f, 0.f, SpawningVolume->Bounds.BoxExtent.Z));
	SpawningVolume->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	SpawningVolume->bGenerateOverlapEvents = false;

	// Create and setup default values for CameraBoom spring component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->RelativeRotation = FRotator(-90.f, 0.f, 0.f);

	// Create and setup default values for the main camera
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	TopDownCamera->OrthoWidth = 1500.f;
	TopDownCamera->bConstrainAspectRatio = true;
	TopDownCamera->AspectRatio = 1.f;
	TopDownCamera->SetAbsolute(false, false, true);	

}

// Called when the game starts or when spawned
void ALevelProps::BeginPlay()
{
	Super::BeginPlay();
	
	// Set view target 
	APlayerController* PlayerCont = GetWorld()->GetFirstPlayerController();
	if (PlayerCont)
	{
		PlayerCont->SetViewTarget(this);
	}
	
}

// Called every frame
void ALevelProps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Returns a random vector in a given volume
FVector ALevelProps::GetRandomPointsInVolume() const
{
	FVector BoxExtent = SpawningVolume->Bounds.BoxExtent;
	FVector Origin = SpawningVolume->Bounds.Origin;
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);

	return RoundToMultiple(RandomPoint, 100);
}
// Rounds vector to multiples of given int
FVector ALevelProps::RoundToMultiple(const FVector VectorToRound, const int32 Multiple) const
{	
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

	return NewVec;
}


