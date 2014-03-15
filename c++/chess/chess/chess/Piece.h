#ifndef CHESS_PIECE
#define CHESS_PIECE

#include "chess.h"

namespace Chess {
	class Piece {
		int value;
		Colour colour;
		string name;
		string shortName;
	  public:
		Piece(int _value, Colour _colour, const string _name, const char _shortName);
		int GetValue();
		string GetName();
		string GetShortName();
	};
}

#endif
