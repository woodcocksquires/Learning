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

vector<int> Queen::GetPossibleMoves(){
	return GetMultiDirectionMoves(-1);
}
