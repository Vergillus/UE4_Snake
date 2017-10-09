// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelProps.generated.h"

UCLASS()
class MYSNAKE_API ALevelProps : public AActor
{
	GENERATED_BODY()
	
	// Static mesh component for ground
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = LevelProps, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Floor;

	// The main camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCamera;

	// Spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// A volume to spawn food
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpawningVolume;
	
public:	
	// Sets default values for this actor's properties
	ALevelProps();

	FORCEINLINE class UStaticMeshComponent* GetFloor() const { return Floor; };
	FORCEINLINE class UCameraComponent* GetCamera() const { return TopDownCamera; };
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; };
	FORCEINLINE class UBoxComponent* GetSpawningVolume() const { return SpawningVolume; };

	// Returns a random vector in a given volume
	UFUNCTION()
	FVector GetRandomPointsInVolume() const;

	// Rounds numbers to multiples of given int
	UFUNCTION()
	FVector RoundToMultiple(const FVector VectorToRound, const int32 Multiple) const;

	/*UFUNCTION()
	void SpawnMyActor();*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class AMySpawnActor> ItemToSpawn;*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
