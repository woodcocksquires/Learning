#ifndef MOVE_CPP_INCLUDED
#define MOVE_CPP_INCLUDED

/*#include "move.h"
#include "ChessUtils.h"
#include "Board.h"
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace Chess;

Move::Move(string _startPosition, string _endPosition, Board * board){

    startPositionString = _startPosition;
    endPositionString = _endPosition;

    int startRow, startCol, endRow, endCol;
    startRow = ((int)_startPosition[1])-48-1;
    endRow = ((int)_endPosition[1])-48-1;
    startCol = Move::GetColumn(_startPosition[0]);
    endCol = Move::GetColumn(_endPosition[0]);

    startBoardPosition = startRow * 8 + startCol;
    endBoardPosition = endRow * 8 + endCol;

    Piece * movePiece, * takenPiece;
    movePiece = board->PieceAtPosition(startRow, startCol);
    takenPiece = board->PieceAtPosition(endRow, endCol);
    char * pieceIdentifier = &(movePiece->GetShortName()[1]);
    moveString = (pieceIdentifier == (char *)'P' ? "" : pieceIdentifier);
    moveString += (takenPiece == nullptr ? "" : "x");
    moveString += (char)(97+endCol);
    moveString += (endRow - 48);
}

int Move::GetColumn(char columnChar){
    if(columnChar > 96){
        columnChar = columnChar - 32;
    }

    for(int r=0; r<8; r++){
        if(Utility::ColumnNames[r] == columnChar){
            return r;
        }
    }

    return -1;
}*/


#endif // MOVE_CPP_INCLUDED
