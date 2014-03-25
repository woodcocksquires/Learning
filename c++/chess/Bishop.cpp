#include "chess.h"
#include "piece.h"
#include "bishop.h"
#include "board.h"

#include <string>
#include <vector>

using namespace std;
using namespace Chess;

Bishop::Bishop(Colour _colour, int _boardPosition, Board * _board):
		Piece(0, _colour, "Bishop", 'B', _boardPosition, _board) {}

vector<int> * Bishop::GetPossibleMoves(){
	return GetOffsetMoves(-1, true);
}

Piece * Bishop::CopyTo(Board * _board){
	return Piece::MakePiece<Bishop>(this, _board);
}
