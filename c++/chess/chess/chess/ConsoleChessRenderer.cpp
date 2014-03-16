#include <iostream>
#include "ConsoleChessRenderer.h"
#include "Board.h"
#include "Chess.h"
#include "ChessUtils.h"
#include "Move.h"

using namespace Chess::Renderer;
using namespace Chess;


void ConsoleChessRenderer::RenderBoard(Board * board, bool inverse) {
    if(!inverse){
        for(int r = 7; r>=0; r--){
            RenderBoardRow(board, r, inverse);
        }
    }
    else {
        for(int r = 0; r<8; r++){
            RenderBoardRow(board, r, inverse);
        }
    }
    RenderBoardRowBorder();
    RenderBoardLabelRow(inverse);
    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRow(Board * board, int offset, bool inverse){
    RenderBoardRowBorder();
    RenderBoardRowInner(ConsoleRowInnerType::Surround, board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Spacer, board, offset, inverse);
    RenderBoardRowContent(board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Spacer, board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Surround, board, offset, inverse);
}

void ConsoleChessRenderer::RenderBoardRowBorder(){
    cout << "   ";
    for(int c=1; c<=8; c++)
    {
        cout << "+--------";
        if(c==8){
            cout << "+";
        }
    }
    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowInner(ConsoleRowInnerType type, Board * board, int offset, bool inverse){
    switch(type)
    {
        case ConsoleRowInnerType::Surround:
            RenderBoardRowNonContent(offset, inverse, false);
            break;
        case ConsoleRowInnerType::Spacer:
            RenderBoardRowNonContent(offset, inverse, true);
            break;
        case ConsoleRowInnerType::Content:
            RenderBoardRowContent(board, offset, inverse);
            break;
    }
}

void ConsoleChessRenderer::RenderBoardRowNonContent(int offset, bool inverse, bool isSpacer){
    cout << "   ";

    if(!inverse){
        for(int c=0; c<8; c++)
        {
            RenderBoardRowNonContentColumn(offset, c, inverse, isSpacer);
        }
    }
    else{
        for(int c=7; c>=0; c--)
        {
            RenderBoardRowNonContentColumn(offset, c, inverse, isSpacer);
        }
    }

    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowNonContentColumn(int row, int col, bool inverse, bool isSpacer){
    cout << "|";
    Colour squareColour = GetSquareColour(row, col);
    if(squareColour == Colour::Black){
        cout << "        ";
    }
    else{
        cout << "##";
        cout << (isSpacer ? "    " : "####");
        cout << "##";
    }

    if((inverse && col==0 ) || (!inverse && col==7)){
        cout << "|";
    }
}

void ConsoleChessRenderer::RenderBoardRowContent(Board * board, int offset, bool inverse){
    cout << " " << (offset + 1) << " ";

    if(!inverse){
        for(int c=0; c<8; c++)
        {
            RenderBoardRowContentColumn(board, offset, c, inverse);
        }
    }
    else{
        for(int c=7; c>=0; c--)
        {
            RenderBoardRowContentColumn(board, offset, c, inverse);
        }
    }

    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowContentColumn(Board* board, int row, int col, bool inverse){
    cout << "|";
    Colour squareColour = GetSquareColour(row, col);
    Piece * piece = board->PieceAtPosition(row, col);
    if(squareColour == Colour::Black){
        cout << "   ";
        cout << (piece == nullptr ? "  " : piece->GetShortName());
        cout << "   ";
    }
    else{
        cout << "## ";
        cout << (piece == nullptr ? "  ": piece->GetShortName());
        cout << " ##";
    }

    if((inverse && col==0) || (!inverse && col==7)){
        cout << "|";
    }
}

void ConsoleChessRenderer::RenderBoardLabelRow(bool inverse){
    cout << "    ";
    if(!inverse){
        for(int c=0; c<8; c++){
            cout << "   " << Utility::ColumnNames[c] << "     ";
        }
    }
    else{
        for(int c=7; c>=0; c--){
            cout << "   " << Utility::ColumnNames[c] << "     ";
        }
    }
    cout << endl;
}

Colour ConsoleChessRenderer::GetSquareColour(int rowOffset, int colOffset){
    return (((rowOffset % 2) + (colOffset % 2)) % 2 == 0) ? Colour::White : Colour::Black;
}

void ConsoleChessRenderer::StartGame(){
    cout << "Welcome to Console Chess!" << endl << endl << endl;
}

PlayerType ConsoleChessRenderer::GetPlayerType(Colour colour){
    string input = "";
    const char * colourString = Utility::ColourStrings[colour];

    cout << "Please choose type of player for " << colourString << " from the options below." << endl;
    cout << "   1   Human" << endl;
    cout << "   2   CPU" << endl;
    cout << endl << "Option: ";

    cin >> input;

    while(input != "1" && input != "2"){
        input = "";
        cout << endl << "Incorrect input, please try again." << endl;
        cout << "Option: ";
        cin >> input;
    }

    PlayerType output = (PlayerType)((int)input[0] - 48 - 1);
    cout << endl << "Selected player type for " << colourString << " is " << Utility::PlayerTypeStrings[output] << "." << endl << endl;
    return output;
}

Move * ConsoleChessRenderer::RequestMove(Colour colour, Board * board){
    string startPosition, endPosition;
    cout << endl;
    cout << Utility::ColourStrings[colour] << ", please enter the reference of the piece you would like to move." << endl;
    cout << "Reference: ";
    cin >> startPosition;

    while(!TestBoardReference(startPosition)){
        cout << endl << "Incorrect reference, please try again." << endl << "Reference: ";
        cin >> startPosition;
    }

    cout << endl << "Please enter the reference of the position you would like to move the piece to.";
    cout << endl << "Reference:";
    cin >> endPosition;

    while(!TestBoardReference(endPosition)){
        cout << endl << "Incorrect reference, please try again." << endl << "Reference: ";
        cin >> endPosition;
    }

    return new Move(startPosition, endPosition, board);
}

bool ConsoleChessRenderer::TestBoardReference(string boardReference){
    if(boardReference.length() != 2){
        return false;
    }

    char firstChar, secondChar;
    firstChar = boardReference[0];
    secondChar = boardReference[1];

    if(Move::GetColumn(firstChar) == -1 || secondChar < 49 || secondChar > 56){
        return false;
    }

    return true;
}

void ConsoleChessRenderer::RenderMoves(){

}
