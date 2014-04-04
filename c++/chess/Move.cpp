#ifndef MOVE_CPP_INCLUDED
#define MOVE_CPP_INCLUDED

#include "move.h"
#include "ChessUtils.h"
#include "Board.h"

using namespace std;
using namespace Chess;

Move::Move(int _startBoardPosition, int _endBoardPosition, bool _pieceTaken, char _pieceIdentifier, Colour _colour):
			startBoardPosition(_startBoardPosition), endBoardPosition(_endBoardPosition),
			pieceTaken(_pieceTaken), pieceIdentifier(_pieceIdentifier), colour(_colour){

}

void Move::SetPawnPromotion(Piece * piece){
	pawnPromotion = true;
	pieceIdentifier = piece->GetIdentifier();
}

void Move::SetKingChecked(bool queenSide){
	kingChecked = true;
	queenSideCastle = !queenSide;
}

string Move::ToString(){

}


#endif // MOVE_CPP_INCLUDED
