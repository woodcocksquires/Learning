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
	return GetMultiDirectionMoves(1, includeKing);
}

Piece * King::CopyTo(Board * _board){
	Piece * piece = Piece::MakePiece<King>(this, _board);
	_board->SetPieceAtPosition(piece);
	return piece;
}

void King::SetChecked(){
	checked = true;
}

bool King::GetChecked(){
	return checked;
}
