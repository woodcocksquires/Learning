#ifndef CHESS_PIECE_KNIGHT
#define CHESS_PIECE_KNIGHT

#include "chess.h"
#include "piece.h"

namespace Chess {
	class Knight: public Piece {
	  public:
		Knight(PieceColour _colour);
		virtual string GetName();
	};
}

#endif