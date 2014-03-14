#ifndef CHESS_UTILS
#define CHESS_UTILS

#include "chesspieces.h"

namespace Chess {
	class Utility {
	  public:
		static void InitialisePieces(Piece ** pPieces, Colour colour);
		static const char * const ColourStrings[2];
	};
}

#endif
