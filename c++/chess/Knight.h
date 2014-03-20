#ifndef CHESS_PIECE_KNIGHT
#define CHESS_PIECE_KNIGHT

#include "chess.h"
#include "piece.h"
#include "board.h"

namespace Chess {
	class Knight: public Piece {
	  public:
		Knight(Colour _colour, int _boardPosition, Board * _board);
	};
}

#endif
