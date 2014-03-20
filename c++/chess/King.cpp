#include "chess.h"
#include "piece.h"
#include "king.h"
#include <string>
using namespace std;
using namespace Chess;

King::King(Colour _colour, int _boardPosition, Board * _board):
		Piece(0, _colour, "King", 'K', _boardPosition, _board) {}
