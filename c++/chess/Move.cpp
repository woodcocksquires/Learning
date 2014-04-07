#ifndef MOVE_CPP_INCLUDED
#define MOVE_CPP_INCLUDED

#include "move.h"
#include "ChessUtils.h"
#include "Board.h"

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

void Move::SetKingChecked(bool checked){
	kingChecked = checked;
}

void Move::SetIsCastleMove(bool queenSide){
	isCastleMove = true;
	queenSideCastle = queenSide;
}

void Move::SetTaken(){
	pieceTaken = true;
}

Colour Move::GetColour(){
	return colour;
}

string Move::ToString(){
	if(isCastleMove){
		return (queenSideCastle ? "0-0-0" : "0-0");
	}

	string output;
	if(pieceIdentifier != 'P' && !pawnPromotion){
		output.push_back(pieceIdentifier);
	}
	output.append(Board::GetBoardPosition(startBoardPosition));
	output.append(pieceTaken ? "x" : "-");
	output.append(Board::GetBoardPosition(endBoardPosition));

	if(pawnPromotion){
		output.append("=");
		output.push_back(pieceIdentifier);
	}

	output.append(kingChecked ? "+" : "");
	return output;
}


#endif // MOVE_CPP_INCLUDED
