#include "chess.h"
#include "piece.h"
#include "board.h"
#include "pawn.h"
#include <string>
using namespace std;
using namespace Chess;

Pawn::Pawn(Colour _colour, int _boardPosition, Board * _board):
		Piece(1, _colour, "Pawn", 'P', _boardPosition, _board) {}
