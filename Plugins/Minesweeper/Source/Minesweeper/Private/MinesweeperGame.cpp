#include "MinesweeperGame.h"

void FMinesweeperGame::StartNewGame(const int rows, const int columns, const int mines)
{
    State = Open;
    
    Rows = rows;
    Columns = columns;

    const int totalPositions = Rows * Columns;
    TotalSafePositions = totalPositions - mines;
    MaxPosition = totalPositions - 1;
    
    VisitedPositions.Empty();    
    MinePositions.Empty();    
        
    while(MinePositions.Num() < mines)
    {
        const uint16 NewMinePosition = FMath::RandRange(0, (rows * columns) - 1);

        if(!MinePositions.Contains(NewMinePosition))
        {
            MinePositions.Emplace(NewMinePosition);
        }
    }
}

FMinesweeperGame::EMinesweeperGameState FMinesweeperGame::ProcessSelection(const int selectedPosition, TMap<int, FText>& revealPositionsOut)
{
    if(State != Open) { return State; }
    
    if(MinePositions.Contains(selectedPosition))
    {
        revealPositionsOut.Add(MakeTuple(selectedPosition, FText::FromString("*")));
        
        State = Lost;
    }
    else
    {
        TraverseGrid(selectedPosition, revealPositionsOut);

        if(TotalSafePositions == VisitedPositions.Num()) { State =  Won; }    
    }

    return State;
}

FMinesweeperGame::EMinesweeperGameState FMinesweeperGame::GetGameState() const
{
    return State;
}

void FMinesweeperGame::TraverseGrid(const int position, TMap<int, FText>& revealPositionsOut) 
{
    if(position < 0 || position > MaxPosition) { return; }

    VisitedPositions.Add(position);
    
    TArray<int> nextPositionsToVisit;
    
    int mineCount = 0;

    auto processPosition = [this, &mineCount, &nextPositionsToVisit](const int position)
    {
        if(MinePositions.Contains(position))
        {
            ++mineCount;
        }
        else
        {
            nextPositionsToVisit.Add(position);
        }
    };

    // Upper Right
    {
        const int upperRightPos = position - Columns + 1;
        if((upperRightPos > 0) && ((upperRightPos % Columns) != 0))
        {
           processPosition(upperRightPos); 
        }
    }
    // since these rules are very similar to each other,
    //    I scoped them to make sure that variables don't cross contaminate 
    
    // Right
    {
        const int rightPos = position + 1;
        if((rightPos > 0) && (rightPos % Columns != 0))
        {
            processPosition(rightPos); 
        }
    }
        
    // Lower Right
    {
        const int lowerRightPos = position + Columns + 1;
        if(lowerRightPos <= MaxPosition && ((lowerRightPos % Columns) != 0))
        {
           processPosition(lowerRightPos); 
        }
    }
    
    
    // Down
    {
        const int downPos = position + Columns;
        if(downPos <= MaxPosition)
        {
           processPosition(downPos); 
        }    
    }
    
    // Lower Left
    {
        const int lowerLeftPos = position + Columns - 1;
        if(lowerLeftPos <= MaxPosition && ((lowerLeftPos % Columns) != (Columns - 1)))
        {
           processPosition(lowerLeftPos); 
        }   
    }
    
    // Left
    {
        const int leftPos = position - 1;
        if((leftPos % Columns) != (Columns -1))
        {
           processPosition(leftPos); 
        }   
    }
    
    // Upper Left
    {
        const int upLeftPos = position - Columns - 1;
        if(upLeftPos >= 0 && ((upLeftPos % Columns) != (Columns - 1)))
        {
           processPosition(upLeftPos); 
        }
    }
    
    // Up
    {
        const int upPos = position - Columns;
        if(upPos >= 0)
        {
           processPosition(upPos); 
        }
    }
    
    if (mineCount == 0)
    {
        for(int nextPos: nextPositionsToVisit)
        {
            if(VisitedPositions.Contains(nextPos)) { continue; }
            
            TraverseGrid(nextPos,revealPositionsOut);
        }
    }

    FText positionText;
    if(mineCount > 0)
    {
        positionText = FText::AsNumber(mineCount);
    }
    
    revealPositionsOut.Add(position, positionText);
}


