#ifndef CHESS_PIECE
#define CHESS_PIECE

#include "chess.h"

namespace Chess {
	class Piece {
		int value;
		Colour colour;
		string name;
		char shortName;
	  public:
		Piece(int _value, Colour _colour, string _name, char _shortName);
		int GetValue();
		string GetName();
		const char * GetShortName();
	};
}

#endif
