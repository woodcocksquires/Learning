#ifndef CHESS_PIECE
#define CHESS_PIECE

#include "chess.h"

namespace Chess {
	class Piece {
		int value;
		PieceColour colour;
	  public:
		Piece(int _value, PieceColour _colour);
		int GetValue();
		virtual string GetName() = 0;
	};
}

#endif