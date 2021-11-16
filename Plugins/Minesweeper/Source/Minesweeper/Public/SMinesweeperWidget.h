#pragma once

#include "MinesweeperGame.h"


// Manages the UI interactions for the Minesweeper game
class SMinesweeperWidget : public SCompoundWidget
{
public:
    SMinesweeperWidget();
    
    SLATE_BEGIN_ARGS(SMinesweeperWidget):
        _ParentWindow()
    {}
        SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow)
    SLATE_END_ARGS()

    static void Display();
    
    void Construct(const FArguments& InArgs);

private:
    void StartNewGame();
    
    FReply OnGenerateClicked();

    FReply OnGameButtonClicked(const int clickedPosition);

    FMinesweeperGame Game;
    
    TMap<int, TSharedPtr<SButton>> GameButtons;
    TSharedPtr<SWindow>  ParentWindow;
    TSharedPtr<STextBlock> TitleText; 
    TSharedPtr<SVerticalBox> GameUIContainer;

    int Rows;
    int Columns;
    int Mines;
};

