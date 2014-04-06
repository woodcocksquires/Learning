#ifndef MOVE_CPP_INCLUDED
#define MOVE_CPP_INCLUDED

#include "move.h"
#include "ChessUtils.h"
#include "Board.h"
#include <sstream>

using namespace std;
using namespace Chess;

Move::Move(int _startBoardPosition, int _endBoardPosition, bool _pieceTaken, char _pieceIdentifier, Colour _colour):
			startBoardPosition(_startBoardPosition), endBoardPosition(_endBoardPosition),
			pieceTaken(_pieceTaken), kingChecked(false), queenSideCastle(false),
			pawnPromotion(false), pieceIdentifier(_pieceIdentifier), colour(_colour), isCastleMove(false){

}

void Move::SetPawnPromotion(Piece * piece){
	pawnPromotion = true;
	pieceIdentifier = piece->GetIdentifier();
}

void Move::SetKingChecked(){
	kingChecked = true;
}

void Move::SetIsCastleMove(bool queenSide){
	isCastleMove = true;
	queenSideCastle = queenSide;
}

string Move::ToString(){
	if(isCastleMove){
		return (queenSideCastle ? "0-0-0" : "0-0");
	}

	// need to add piece promotion to this.
	stringstream ss;
	ss << (pieceIdentifier == 'P' ? "" : string(pieceIdentifier));
	return ss.str();

	/*return (pieceIdentifier == 'P' ? "" : string(pieceIdentifier))
			+ Board::GetBoardPosition(startBoardPosition)
			+ string((pieceTaken ? "x" : "-"))
			+ Board::GetBoardPosition(endBoardPosition)
			+ string((kingChecked ? "+" : ""));*/
}


#endif // MOVE_CPP_INCLUDED
