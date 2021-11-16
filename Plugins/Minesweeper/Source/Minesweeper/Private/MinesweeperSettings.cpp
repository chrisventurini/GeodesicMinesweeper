#include "MinesweeperSettings.h"


UMinesweeperSettings::UMinesweeperSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	DefaultColumns(4),
	DefaultRows(4),
	DefaultMines(2)
{
}


FName UMinesweeperSettings::GetCategoryName() const
{
    return TEXT("Plugins");
}

FText UMinesweeperSettings::GetSectionText() const
{
	return NSLOCTEXT("FMinesweeperModule", "Minesweeper", "Minesweeper");
}
