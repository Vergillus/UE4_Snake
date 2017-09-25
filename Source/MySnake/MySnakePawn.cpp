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


// Sets default values
AMySnakePawn::AMySnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	BoxCollision->BodyInstance.SetCollisionProfileName(TEXT("Pawn"));
	BoxCollision->SetNotifyRigidBodyCollision(true);
	BoxCollision->OnComponentHit.AddDynamic(this, &AMySnakePawn::OnHit);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMySnakePawn::OnActorOverlap);
	RootComponent = BoxCollision;	

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Snake Head"));
	CubeMesh->SetRelativeLocation(FVector(0.0f, 0.f, -50.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshOBJ(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	
	if (CubeMeshOBJ.Succeeded())
	{
		CubeMesh->SetStaticMesh(CubeMeshOBJ.Object);
	}
	BoxCollision->InitBoxExtent(FVector(CubeMesh->Bounds.BoxExtent.X, CubeMesh->Bounds.BoxExtent.Y, CubeMesh->Bounds.BoxExtent.Z));
	
	CubeMesh->SetupAttachment(BoxCollision);

}

// Called when the game starts or when spawned
void AMySnakePawn::BeginPlay()
{
	Super::BeginPlay();	

	//LevelRef = Cast<ALevelProps>(GetWorld()->SpawnActor(ALevelProps::StaticClass()));
	ContRef = Cast<AMySnakeController>(GetWorld()->GetFirstPlayerController());	
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

void AMySnakePawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit!!!!!"));	
}

void AMySnakePawn::OnActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap!!!!!"));
		if (OtherActor->IsA(AMySpawnActor::StaticClass()))
		{
			OtherActor->Destroy();
			
			if (ContRef)
			{
				//LevelRef->SpawnMyActor();	
				ContRef->SpawnSnakeParts();
				ContRef->bIsSnakeGrowing = true;
				//UE_LOG(LogTemp, Warning, TEXT("Spawn!!!!!"));
			}
			
		}
	}
	
}
