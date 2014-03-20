#ifndef CHESS_PIECE_PAWN
#define CHESS_PIECE_PAWN

#include "chess.h"
#include "piece.h"
#include "board.h"

namespace Chess {
	class Pawn: public Piece {
	  public:
		Pawn(Colour _colour, int _boardPosition, Board * _board);
    };
}

#endif
