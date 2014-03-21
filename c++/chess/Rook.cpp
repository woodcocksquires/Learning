#include "chess.h"
#include "piece.h"
#include "rook.h"
#include "board.h"
#include <string>
#include <vector>
using namespace std;
using namespace Chess;

Rook::Rook(Colour _colour, int _boardPosition, Board * _board):
		Piece(5, _colour, "Rook", 'R', _boardPosition, _board) {}

vector<int> * Rook::GetPossibleMoves(){
	return GetOffsetMoves(-1, false);
}
