#ifndef CHESS_PIECE_ROOK
#define CHESS_PIECE_ROOK

#include "chess.h"
#include "piece.h"

namespace Chess {
	class Rook: public Piece {
	  public:
		Rook(PieceColour _colour);
		virtual string GetName();
	};
}

#endif