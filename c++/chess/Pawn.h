#ifndef CHESS_PIECE_PAWN
#define CHESS_PIECE_PAWN

#include "chess.h"
#include "piece.h"
#include "board.h"
#include <vector>

namespace Chess {
	class Pawn: public Piece {
	  public:
		Pawn(Colour _colour, int _boardPosition, Board * _board);
		virtual vector<int> * GetPossibleMoves();
		virtual vector<int> * GetPossibleMoves(bool includeKing);
		virtual Piece * CopyTo(Board * _board);
    };
}

#endif
