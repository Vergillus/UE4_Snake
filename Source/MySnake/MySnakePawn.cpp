// Fill out your copyright notice in the Description page of Project Settings.

#include "MySnakePawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "LevelProps.h"
#include "MySpawnActor.h"
#include "MySnakeController.h"
#include "MySnakeGameMode.h"


// Sets default values
AMySnakePawn::AMySnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and define some default parameters for Box Collision variable
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BoxCollision->BodyInstance.SetCollisionProfileName(TEXT("Pawn"));
	BoxCollision->SetNotifyRigidBodyCollision(true);
	// Create dynamic events for hit and overlap events
	BoxCollision->OnComponentHit.AddDynamic(this, &AMySnakePawn::OnHit);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMySnakePawn::OnActorOverlap);
	// Make BoxCollision component Root component
	RootComponent = BoxCollision;	

	// Create and define some default parameters for CubeMesh variable
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Snake Head"));
	CubeMesh->SetRelativeLocation(FVector(0.0f, 0.f, -50.f));

	// Get the Cube shape from StarterContent
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshOBJ(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	
	// Check the shape is found
	if (CubeMeshOBJ.Succeeded())
	{
		// Assing static mesh
		CubeMesh->SetStaticMesh(CubeMeshOBJ.Object);
	}
	// Set the defalt values for BoxCollision's box extent
	BoxCollision->InitBoxExtent(FVector(CubeMesh->Bounds.BoxExtent.X, CubeMesh->Bounds.BoxExtent.Y, CubeMesh->Bounds.BoxExtent.Z));

	// Setup Attachment
	CubeMesh->SetupAttachment(BoxCollision);

}

// Called when the game starts or when spawned
void AMySnakePawn::BeginPlay()
{
	Super::BeginPlay();	

	// Get the referance of Controller class
	ContRef = Cast<AMySnakeController>(GetWorld()->GetFirstPlayerController());	

	// Get the referance of Gamemode
	GameModeRef = Cast<AMySnakeGameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AMySnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMySnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Called when a Hit event occurs
void AMySnakePawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GameModeRef->SetbIsGameOver(true);
	ContRef->StopMyTimer();
}

// Called when a Overlap event occurs
void AMySnakePawn::OnActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{	
		if (OtherActor->IsA(AMySpawnActor::StaticClass()))
		{
			OtherActor->Destroy();
			
			if (ContRef && GameModeRef)
			{
				//Make the snake grow
				ContRef->SpawnSnakeParts();
				// Spawn Food
				GameModeRef->SpawnFood();
				// Add to score
				GameModeRef->IncrementScore();				
			}
			
		}
	}
	
}
