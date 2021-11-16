#pragma once


// Minesweeper game logic 
class FMinesweeperGame
{
public:

    enum EMinesweeperGameState
    {
        Open,
        Lost,
        Won
    };
    
    void StartNewGame(const int rows, const int columns, const int mines);
    
    EMinesweeperGameState ProcessSelection(const int selectedPosition, TMap<int, FText>& revealPositionsOut);

    EMinesweeperGameState GetGameState() const;

private:

    void TraverseGrid(const int position, TMap<int, FText>& revealPositionsOut);

    EMinesweeperGameState State = Open;
    
    TSet<int> VisitedPositions;
    TSet<int> MinePositions;
    
    int Rows = 0;
    int Columns = 0;
    int Mines = 0;
    
    int MaxPosition = 0;
    int TotalSafePositions = 0;

};


