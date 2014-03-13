#ifndef CHESS_UTILS
#define CHESS_UTILS

#include "chesspieces.h"

namespace Chess {
	class Utility {
	  public:
		static void InitialisePieces(Piece ** pPieces, PieceColour colour);
		static const char * const PieceColourStrings[2];
	};
}

#endif
