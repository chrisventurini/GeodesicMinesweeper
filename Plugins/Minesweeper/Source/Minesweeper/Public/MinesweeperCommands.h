// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MinesweeperStyle.h"

// Defines UI commands for the Minesweeper module 
class FMinesweeperCommands : public TCommands<FMinesweeperCommands>
{
public:

	FMinesweeperCommands()
		: TCommands<FMinesweeperCommands>(TEXT("Minesweeper"), NSLOCTEXT("FMinesweeperModule", "MinesweeperPlugin", "Minesweeper Plugin"), NAME_None, FMinesweeperStyle::GetStyleSetName())
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};