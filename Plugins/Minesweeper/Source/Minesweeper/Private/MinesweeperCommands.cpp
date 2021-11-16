// Copyright Epic Games, Inc. All Rights Reserved.

#include "MineSweeperCommands.h"

#define LOCTEXT_NAMESPACE "FMinesweeperModule"

void FMinesweeperCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Play Minesweeper", "Launch Minesweeper game", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
