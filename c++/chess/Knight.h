#ifndef CHESS_PIECE_KNIGHT
#define CHESS_PIECE_KNIGHT

#include "chess.h"
#include "piece.h"
#include "board.h"
#include <vector>

namespace Chess {
	class Knight: public Piece {
	  public:
		Knight(Colour _colour, int _boardPosition, Board * _board);
		virtual vector<int> * GetPossibleMoves();
		virtual Piece * CopyTo(Board * _board);
	};
}

#endif
