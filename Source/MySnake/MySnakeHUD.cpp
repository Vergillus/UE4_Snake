// Fill out your copyright notice in the Description page of Project Settings.

#include "MySnakeHUD.h"
#include "Engine/Canvas.h"
#include "MySnakeGameMode.h"

AMySnakeHUD::AMySnakeHUD()
{
	//Set defaults
	bCanShow = false;
	PlayerScore = 0;
}


void AMySnakeHUD::BeginPlay()
{
	Super::BeginPlay();

	// Get the GameMode
	GMRef = Cast<AMySnakeGameMode>(GetWorld()->GetAuthGameMode());
}

void AMySnakeHUD::DrawHUD()
{
	Super::DrawHUD();
	// Get the center of canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// Get whether or not the game is over
	bCanShow = GMRef->GetbIsGameOver();

	// Show UI elements when the game is over
	if (bCanShow)
	{	
		if (GMRef)
		{
			// Get the player score from GameMode
			PlayerScore = GMRef->GetScore();
		}		

		// Draw rectangles and corresponding texts 
		DrawRect(FLinearColor::Transparent.Blue, Center.X - 100.f, Center.Y - 12.5f, 200.f, 25.f);
		DrawText("You are DEAD!!!!", FLinearColor::Transparent.White, Center.X - 100.f, Center.Y - 12.5f, 0, 2);

		DrawRect(FLinearColor::Transparent.Blue, Center.X - 100.f, Center.Y + 12.5f, 200.f, 25.f);
		DrawText(FString::Printf(TEXT(" Your Score: %d "),PlayerScore), FLinearColor::Transparent.White, Center.X - 100.f, Center.Y + 12.5f, 0, 2);

		DrawRect(FLinearColor::Transparent.Blue, Center.X - 160.f, Center.Y + 50.f, 310.f, 25.f);
		DrawText("Press 'R' Key To Restart!!", FLinearColor::Transparent.White, Center.X - 150.f, Center.Y + 50.f, 0, 2);
	}
	

}


