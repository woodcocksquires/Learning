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
	vector<int> * moves = new vector<int>();
	moves->push_back();
}
