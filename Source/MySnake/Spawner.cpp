// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "MySpawnActor.h"
#include "LevelProps.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawningVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningVolumeBox"));	
	SpawningVolume->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	SpawningVolume->bGenerateOverlapEvents = false;
	RootComponent = SpawningVolume;

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_OBJ(TEXT("Blueprint'/Game/Blueprints/BP_SpawnActorFood.BP_SpawnActorFood'"));
	if (BP_OBJ.Succeeded())
	{
		ItemToSpawn = (UClass*)BP_OBJ.Object->GeneratedClass;
	}
	//ItemToSpawn = AMySpawnActor::StaticClass();
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();	

	SpawnMyActor();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Spawner TICK"));
	//SpawnMyActor();	

}

FVector ASpawner::GetRandomPointsInVolume()
{
	FVector BoxExtent = SpawningVolume->Bounds.BoxExtent;	
	FVector Origin = SpawningVolume->Bounds.Origin;
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);

	return RoundToMultiple(RandomPoint,100);
}

FVector ASpawner::RoundToMultiple(const FVector VectorToRound, const int32 Multiple)
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
	
	return NewVec;
}

void ASpawner::SpawnMyActor()
{
	if (ItemToSpawn != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("SPAWNER LOG!!!"));
		UWorld* const World = GetWorld();

		if (World)
		{
			FVector SpawnLocation = GetRandomPointsInVolume();						
			SpawnLocation.Z = GetActorLocation().Z;
			World->SpawnActor<AMySpawnActor>(ItemToSpawn, SpawnLocation,FRotator::ZeroRotator);
			//UE_LOG(LogTemp, Warning, TEXT("SPAWN THE FUCK!!!!"));
			
		}
	}
}

