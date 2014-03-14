#ifndef CHESS_PIECE
#define CHESS_PIECE

#include "chess.h"

namespace Chess {
	class Piece {
		int value;
		Colour colour;
	  public:
		Piece(int _value, Colour _colour);
		int GetValue();
		virtual string GetName() = 0;
	};
}

#endif
