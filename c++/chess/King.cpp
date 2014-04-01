#include "chess.h"
#include "piece.h"
#include "king.h"
#include <string>
#include <vector>

using namespace std;
using namespace Chess;

King::King(Colour _colour, int _boardPosition, Board * _board):
		Piece(0, _colour, "King", 'K', _boardPosition, _board), checked(false) {}

vector<int> * King::GetPossibleMoves(){
	return GetPossibleMoves(false);
}

vector<int> * King::GetPossibleMoves(bool includeKing){
	vector<int> * moves = GetMultiDirectionMoves(1, includeKing);
	if(board->TestCastlingMove(colour, false)){
		moves->push_back((colour == Colour::White ? 6 : 62));
	}

	if(board->TestCastlingMove(colour, true)){
		moves->push_back((colour == Colour::White ? 2 : 58));
	}
	return moves;
}

Piece * King::CopyTo(Board * _board){
	Piece * piece = Piece::MakePiece<King>(this, _board);
	_board->SetPieceAtPosition(piece);
	return piece;
}

void King::SetChecked(bool value){
	checked = value;
}

bool King::GetChecked(){
	return checked;
}
