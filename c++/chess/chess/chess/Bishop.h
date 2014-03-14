#ifndef CHESS_PIECE_BISHOP
#define CHESS_PIECE_BISHOP

#include "chess.h"
#include "piece.h"

namespace Chess {
	class Bishop: public Piece {
	  public:
		Bishop(Colour _colour);
		virtual string GetName();
	};
}

#endif
