// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MySnakeHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYSNAKE_API AMySnakeHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AMySnakeHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	
private:

	UPROPERTY()
	bool bCanShow;

	UPROPERTY()
	int PlayerScore;

	UPROPERTY()
	class AMySnakeGameMode* GMRef;
};
