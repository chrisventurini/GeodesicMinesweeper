// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FToolBarBuilder;
class FMenuBuilder;

// Manages the startup and shutdown of the Minesweeper module 
class FMinesweeperModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static void PluginButtonClicked();
	
private:

	void RegisterMenus();

	TSharedPtr<class FUICommandList> PluginCommands;
};
