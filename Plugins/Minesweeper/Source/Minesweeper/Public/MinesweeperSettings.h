#pragma once

#include "Engine/DeveloperSettings.h"
#include "MinesweeperSettings.generated.h"

// Defines default project settings for the the Minesweeper plugin
//    Specifically when the game is launched, what is the starting number of columns, rows, and mines
UCLASS(Config=Minesweeper, defaultconfig, meta=(DisplayName="Minesweeper"))
class UMinesweeperSettings : public UDeveloperSettings
{
private:
    GENERATED_UCLASS_BODY()
   
public:

public:
    virtual FName GetCategoryName() const override;
#if WITH_EDITOR
    virtual FText GetSectionText() const override;
#endif

    UPROPERTY(config=Minesweeper, EditAnywhere, DisplayName="Default Number of Columns", meta=(ClampMin="3", ClampMax="20"), Category="Defaults")
    int DefaultColumns;
    
    UPROPERTY(config=Minesweeper, EditAnywhere, DisplayName="Default Number of Rows", meta=(ClampMin="3", ClampMax="20"), Category="Defaults")
    int DefaultRows;

    UPROPERTY(config=Minesweeper, EditAnywhere, DisplayName="Default Number of Mines", meta=(ClampMin="1", ClampMax="399"), Category="Defaults")
    int DefaultMines;
};

