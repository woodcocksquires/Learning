#ifndef CHESS_PIECE_QUEEN
#define CHESS_PIECE_QUEEN

#include "chess.h"
#include "piece.h"

namespace Chess {
	class Queen: public Piece {
	  public:
		Queen(PieceColour _colour);
		virtual string GetName();
	};
}

#endif