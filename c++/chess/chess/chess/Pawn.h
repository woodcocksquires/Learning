#ifndef CHESS_PIECE_PAWN
#define CHESS_PIECE_PAWN

#include "chess.h"
#include "piece.h"

namespace Chess {
	class Pawn: public Piece {
	  public:
		Pawn(PieceColour _colour);
		virtual string GetName();
	};
}

#endif