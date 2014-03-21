#include "chess.h"
#include "piece.h"
#include "bishop.h"
#include <string>
#include <vector>

using namespace std;
using namespace Chess;

Bishop::Bishop(Colour _colour, int _boardPosition, Board * _board):
		Piece(0, _colour, "Bishop", 'B', _boardPosition, _board) {}

vector<int> * Bishop::GetPossibleMoves(){
	return moves = GetOffsetMoves(-1, true);
}
