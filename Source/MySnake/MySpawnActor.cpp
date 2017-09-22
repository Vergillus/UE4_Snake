// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpawnActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AMySpawnActor::AMySpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Root Component"));
	SphereCollision->BodyInstance.SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = SphereCollision;

	SpawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SpawnMeshOBJ(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (SpawnMeshOBJ.Succeeded())
	{
		SpawnMesh->SetStaticMesh(SpawnMeshOBJ.Object);
	}

	SpawnMesh->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	SpawnMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AMySpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

