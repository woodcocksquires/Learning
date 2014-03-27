#include "chess.h"
#include "piece.h"
#include "queen.h"
#include "board.h"
#include <string>
#include <vector>
using namespace std;
using namespace Chess;

Queen::Queen(Colour _colour, int _boardPosition, Board * _board):
		Piece(9, _colour, "Queen", 'Q', _boardPosition, _board) {}

vector<int> * Queen::GetPossibleMoves(){
	return GetPossibleMoves(false);
}

vector<int> * Queen::GetPossibleMoves(bool includeKing){
	return GetMultiDirectionMoves(-1, includeKing);
}

Piece * Queen::CopyTo(Board * _board){
	Piece * piece = Piece::MakePiece<Queen>(this, _board);
	_board->SetPieceAtPosition(piece);
	return piece;
}
