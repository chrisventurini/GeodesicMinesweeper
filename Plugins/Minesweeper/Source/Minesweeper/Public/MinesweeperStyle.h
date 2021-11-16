// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

// Reusable style names to avoid magic strings sprinkled throughout UI/style code
namespace MinesweeperStyleNames
{
	const FName MineWonButton("Minesweeper.MineWonButton");
	const FName MineLostButton("Minesweeper.MineLostButton");
	const FName UnrevealedButton("Minesweeper.UnrevealedButton");
	const FName GameButtonText("Minesweeper.GameButtonText");
	const FName GameTitleText("Minesweeper.GameTitleText");
}

// Defines the non-default UI styling for the Minesweeper plugin 
class FMinesweeperStyle
{
public:

	static void Initialize();

	static void Shutdown();

	static void ReloadTextures();

	static const ISlateStyle& Get();

	static const FButtonStyle* GetButtonStyle(FName StyleName);
	
	static FName GetStyleSetName();

private:

	static TSharedRef< class FSlateStyleSet > Create();
	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};