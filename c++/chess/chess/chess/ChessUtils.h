#ifndef CHESS_UTILS
#define CHESS_UTILS

#include "chesspieces.h"

namespace Chess {
	class Utility {
	  public: 
		static void InitialisePieces(Piece ** pPieces, PieceColour colour);
	};
}

#endif