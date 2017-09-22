// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class MYSNAKE_API ASpawner : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpawningVolume;
		
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UFUNCTION()
	FVector GetRandomPointsInVolume();

	FVector RoundToMultiple(const FVector VectorToRound, const int32 Multiple);

	UFUNCTION()
	void SpawnMyActor();	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<class AMySpawnActor> ItemToSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
