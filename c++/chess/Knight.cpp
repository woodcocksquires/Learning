#include "chess.h"
#include "piece.h"
#include "knight.h"
#include <string>
using namespace std;
using namespace Chess;

Knight::Knight(Colour _colour, int _boardPosition, Board * _board):
		Piece(3, _colour, "Knight", 'N', _boardPosition, _board) {}
