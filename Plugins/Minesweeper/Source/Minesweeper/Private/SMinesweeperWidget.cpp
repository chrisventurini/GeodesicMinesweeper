
#include "SMinesweeperWidget.h"

#include "MinesweeperSettings.h"
#include "MinesweeperStyle.h"
#include "Slate/Public/Widgets/Layout/SSeparator.h"
#include "SlateCore/Public/Widgets/SBoxPanel.h"
#include "Widgets/Input/SSpinBox.h"

#define LOCTEXT_NAMESPACE "FMinesweeperModule"

// Organizing the localized text centrally 
namespace
{
    const FText LETS_PLAY_TEXT = LOCTEXT("LetsPlayMinesweeper", "Let's Play Minesweeper!");
    const FText YOU_WON_TEXT = LOCTEXT("YouWon", "You won!! :)");
    const FText YOU_LOST_TEXT = LOCTEXT("YouLost", "You Lost :(");
    const FText COLUMNS_TEXT = LOCTEXT("Columns", "Columns");
    const FText ROWS_TEXT = LOCTEXT("Rows", "Rows");
    const FText GEN_BOARD_TEXT = LOCTEXT("GenerateBoard", "Generate Board");
    const FText NUM_OF_MINES_TEXT = LOCTEXT("NumberOfMines", "Number of Mines");
}

SMinesweeperWidget::SMinesweeperWidget()
{
	auto* defaultSettings = GetDefault<UMinesweeperSettings>();

    Rows = defaultSettings->DefaultRows;
    Columns = defaultSettings->DefaultColumns;
    Mines = defaultSettings->DefaultMines;
}

void SMinesweeperWidget::Display()
{
    TSharedPtr<SWindow> Window = SNew(SWindow)
                        .Title(LOCTEXT("Minesweeper", "Minesweeper"))
                        .SupportsMaximize(false)
                        .SupportsMinimize(false)
                        .bDragAnywhere(true)
                        .IsTopmostWindow(true)
                        .FocusWhenFirstShown(true)
                        .MinHeight(800.f)
                        .MinWidth(700.f)
                        .AutoCenter(EAutoCenter::PreferredWorkArea);

    const TSharedRef<SMinesweeperWidget> WebWidget = SNew(SMinesweeperWidget)
                                                    .ParentWindow(Window);

    Window->SetContent(WebWidget);
    FSlateApplication::Get().AddWindow(Window.ToSharedRef());
}

void SMinesweeperWidget::Construct(const FArguments& InArgs)
{
    ParentWindow = InArgs._ParentWindow;

    const FMargin defaultMargin(1.5f, 0.0f, 10.0f, 0.0f);
    const FMargin separatorMargin(0.0f, 10.0f, 0.0f, 10.0f);

    ChildSlot
       [
           SNew(SVerticalBox)
                +SVerticalBox::Slot()
                    .Padding(1.5f, 10.0f, 10.0f, 5.0f)
                    .AutoHeight()
                    
           [
                SAssignNew(TitleText, STextBlock)
                   .TextStyle(FMinesweeperStyle::Get(), MinesweeperStyleNames::GameTitleText)
                   .Justification(ETextJustify::Center)
                   .Text(LETS_PLAY_TEXT)
           ]
            +SVerticalBox::Slot()
                .AutoHeight()
                .Padding(separatorMargin)
                [
                    SNew(SSeparator)
                        .Orientation(EOrientation::Orient_Horizontal)
                        .Thickness(3.0f)
                ]
            +SVerticalBox::Slot()
               .AutoHeight()
           [
               SNew(SHorizontalBox)
                   +SHorizontalBox::Slot()
                       .Padding(defaultMargin)
                       .AutoWidth()
                   [
                       SNew(STextBlock)
                          .Text(COLUMNS_TEXT)
                   ]
                   +SHorizontalBox::Slot()
                       .Padding(defaultMargin)
                   [
                       SNew(SSpinBox<int>)
                           .Value(Columns)
                           .MaxValue(20)
                           .MinValue(3)
                           .OnValueChanged_Lambda([this](uint16 value) { Columns = value; })
                   ]
                   +SHorizontalBox::Slot()
                       .Padding(defaultMargin)
                       .AutoWidth()
                   [
                      SNew(STextBlock)
                         .Text(ROWS_TEXT)
                   ]
                   +SHorizontalBox::Slot()
                       .Padding(defaultMargin)
                   [
                       SNew(SSpinBox<int>)
                           .Value(Rows)
                           .MaxValue(20)
                           .MinValue(3)
                           .OnValueChanged_Lambda([this](uint16 value) { Rows = value; })
                   ]
                   +SHorizontalBox::Slot()
                      .Padding(defaultMargin)
                      .AutoWidth()
                   [
                      SNew(STextBlock)
                         .Text(NUM_OF_MINES_TEXT)
                   ]
                   +SHorizontalBox::Slot()
                       .Padding(defaultMargin)
                   [
                       SNew(SSpinBox<uint16>)
                           .Value(Mines)
                           .MinValue(1)
                           .OnValueChanged_Lambda([this](uint16 value) { Mines = value; })
                           .MaxValue_Lambda([this]
                              {
                                  return (Rows * Columns) - 1;
                              })
                   ]
           ]
            +SVerticalBox::Slot()
                .AutoHeight()
                .Padding(5.0f, 5.0f)
                [
                    SNew(SButton)
                        .Text(GEN_BOARD_TEXT)
                        .HAlign(HAlign_Center)
                        .OnClicked_Raw(this, &SMinesweeperWidget::OnGenerateClicked)
                ]
            +SVerticalBox::Slot()
                    .AutoHeight()
                    .Padding(separatorMargin)
                    [
                        SNew(SSeparator)
                            .Orientation(EOrientation::Orient_Horizontal)
                            .Thickness(3.0f)
                    ]
            +SVerticalBox::Slot()
                .AutoHeight()
                [
                    SAssignNew(GameUIContainer, SVerticalBox)
                ]
       ];

    StartNewGame();
}

FReply SMinesweeperWidget::OnGenerateClicked()
{
    GameUIContainer->ClearChildren();
    
    TitleText->SetText(LETS_PLAY_TEXT);
    StartNewGame();
    
    return FReply::Handled();
}

void SMinesweeperWidget::StartNewGame()
{
    Game.StartNewGame(Rows, Columns, Mines);

    GameUIContainer->ClearChildren();

    GameButtons.Empty();
    
    for (uint16 rowIdx = 0; rowIdx < Rows; ++rowIdx)
    {
        const TSharedRef<SHorizontalBox> roxBox = SNew(SHorizontalBox);
        
        for (uint16 columnIdx = 0; columnIdx < Columns; ++columnIdx)
        {
            const int btnPosition = (rowIdx * Columns) + columnIdx;
            
            TSharedRef<SButton> gameBtn = SNew(SButton)
                                            .HAlign(EHorizontalAlignment::HAlign_Center)
                                            .OnClicked_Raw(
                                        this,
                                                   &SMinesweeperWidget::OnGameButtonClicked,
                                                   btnPosition
                                            );

            roxBox->AddSlot()
                .MaxWidth(60.0f)
            [
                gameBtn
            ];

            GameButtons.Add(btnPosition, gameBtn);
        }

        GameUIContainer->AddSlot()[roxBox];
    }
}

FReply SMinesweeperWidget::OnGameButtonClicked(const int clickedPosition)
{
    TMap<int, FText> toRevealPositions;
        
    const FMinesweeperGame::EMinesweeperGameState gameState = Game.ProcessSelection(clickedPosition, toRevealPositions);

    auto setBtnFunc = [](TSharedPtr<SButton> btn, FText text, const FButtonStyle* style = nullptr)
    {
        btn->SetEnabled(false);
        btn->SetContent(
            SNew(STextBlock)
                .TextStyle(FMinesweeperStyle::Get(), MinesweeperStyleNames::GameButtonText )
                .Text(text)
        );

        if(style)
        {
            btn->SetButtonStyle(style);
        }
    };
    
    for (TPair<int, FText>& revealPosition : toRevealPositions)
    {
        setBtnFunc(
            GameButtons[revealPosition.Key],
            revealPosition.Value,
            (gameState == FMinesweeperGame::Lost) ?
                    FMinesweeperStyle::GetButtonStyle(MinesweeperStyleNames::MineLostButton) :
                    nullptr
       );

        // We don't need to process it again and will optimize the end state loop
        GameButtons.Remove(revealPosition.Key);   
    }

    if(gameState != FMinesweeperGame::EMinesweeperGameState::Open)
    {
        TitleText->SetText((gameState == FMinesweeperGame::Won) ? YOU_WON_TEXT : YOU_LOST_TEXT);
        
        for (TPair<int, TSharedPtr<SButton>>& btnPair : GameButtons)
        {
            if(gameState == FMinesweeperGame::Won)
            {
                setBtnFunc(btnPair.Value,
                    FText::FromString("*"), // If we won, we know that only bombs are left
                    FMinesweeperStyle::GetButtonStyle(MinesweeperStyleNames::MineWonButton)
                );  
            }
            else
            {
                setBtnFunc(btnPair.Value,
                    FText::FromString(""), 
                    FMinesweeperStyle::GetButtonStyle(MinesweeperStyleNames::UnrevealedButton)
                );
            }
            
        }
    }
    
    return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
