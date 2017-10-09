// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MySnakePawn.generated.h"

UCLASS()
class MYSNAKE_API AMySnakePawn : public APawn
{
	GENERATED_BODY()
	
	// Collision component that checks whether a collision happends or not
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta= (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;

	// Static mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CubeMesh;
	
public:
	// Sets default values for this pawn's properties
	AMySnakePawn();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// Hit function to check hit events
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);	

	// Overlap function to check overlap events
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComp,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
	// Referance pointer to LevelProps class
	UPROPERTY()
	class ALevelProps* LevelRef;
	
	// Referance pointer to MySnakeController class
	UPROPERTY()
	class AMySnakeController* ContRef;

	// Referance pointer to MySnakeGameMode class
	UPROPERTY()
	class AMySnakeGameMode* GameModeRef;

};
