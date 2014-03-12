#ifndef CHESS_PIECE_KING
#define CHESS_PIECE_KING

#include "chess.h"
#include "piece.h"

namespace Chess {
	class King: public Piece {
	  public:
		King(PieceColour _colour);
		virtual string GetName();
	};
}

#endif