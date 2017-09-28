// Fill out your copyright notice in the Description page of Project Settings.

#include "MySnakeHUD.h"
#include "Engine/Canvas.h"
#include "MySnakeGameMode.h"

AMySnakeHUD::AMySnakeHUD()
{
	bCanShow = false;
	PlayerScore = 0;
}


void AMySnakeHUD::BeginPlay()
{
	Super::BeginPlay();

	GMRef = Cast<AMySnakeGameMode>(GetWorld()->GetAuthGameMode());
}

void AMySnakeHUD::DrawHUD()
{
	Super::DrawHUD();

	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	bCanShow = GMRef->GetbIsGameOver();

	//UE_LOG(LogTemp, Warning, TEXT("Game Over !? %s"), bCanShow ? TEXT("true") : TEXT("false"));

	if (bCanShow)
	{	
		if (GMRef)
		{
			PlayerScore = GMRef->GetScore();
		}		

		//DrawRect(FLinearColor::Transparent.Black, Center.X - 325.f, Center.Y - 325.f, Canvas->SizeX, Canvas->SizeY);

		DrawRect(FLinearColor::Transparent.Blue, Center.X - 100.f, Center.Y - 12.5f, 200.f, 25.f);
		DrawText("You are DEAD!!!!", FLinearColor::Transparent.White, Center.X - 100.f, Center.Y - 12.5f, 0, 2);

		DrawRect(FLinearColor::Transparent.Blue, Center.X - 100.f, Center.Y + 12.5f, 200.f, 25.f);
		DrawText(FString::Printf(TEXT(" Your Score: %d "),PlayerScore), FLinearColor::Transparent.White, Center.X - 100.f, Center.Y + 12.5f, 0, 2);

		DrawRect(FLinearColor::Transparent.Blue, Center.X - 160.f, Center.Y + 50.f, 310.f, 25.f);
		DrawText("Press 'R' Key To Restart!!", FLinearColor::Transparent.White, Center.X - 150.f, Center.Y + 50.f, 0, 2);		

	}
	

}


