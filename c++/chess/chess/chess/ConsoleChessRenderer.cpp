#include <iostream>
#include "ConsoleChessRenderer.h"
#include "Board.h"
#include "Chess.h"

using namespace Chess::Renderer;
using namespace Chess;


void ConsoleChessRenderer::RenderBoard(Board * board, bool inverse) {
    for(int r = 7; r>=0; r--){
        RenderBoardRow(board, r, false);
    }
    RenderBoardRowBorder();
}

void ConsoleChessRenderer::RenderBoardRow(Board * board, int offset, bool inverse){
    RenderBoardRowBorder();
    RenderBoardRowInner(ConsoleRowInnerType::Surround, board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Spacer, board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Spacer, board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Surround, board, offset, inverse);
}

void ConsoleChessRenderer::RenderBoardRowBorder(){
    cout << "   ";
    for(int c=1; c<=8; c++)
    {
        cout << "+------";
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

    for(int c=0; c<8; c++)
    {
        cout << "|";
        Colour squareColour = GetSquareColour(offset, c);
        if(squareColour == Colour::White){
            cout << "      ";
        }
        else{
            cout << "##";
            cout << (isSpacer ? "  " : "##");
            cout << "##";
        }

        if(c==7){
            cout << "|";
        }
    }

    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowContent(Board * board, int offset, bool inverse){
    cout << "   ";

    for(int c=0; c<8; c++)
    {
        cout << "|";
        Colour squareColour = GetSquareColour(offset, c);
        Piece * piece = board->PieceAtPosition(offset, c);
        if(squareColour == Colour::White){
            cout << "      ";
        }
        else{
            cout << "##";
            cout << piece == nullptr ? "  " : piece->GetShortName();
            cout << "##";
        }

        if(c==7){
            cout << "|";
        }
    }

    cout << endl;
}

Colour ConsoleChessRenderer::GetSquareColour(int rowOffset, int colOffset){
    return (((rowOffset % 2) + (colOffset % 2)) % 2 == 0) ? Colour::White : Colour::Black;
}
