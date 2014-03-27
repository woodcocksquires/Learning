#ifndef CHESS_PIECE_QUEEN
#define CHESS_PIECE_QUEEN

#include "chess.h"
#include "piece.h"
#include "board.h"
#include <vector>

namespace Chess {
	class Queen: public Piece {
	  public:
		Queen(Colour _colour, int _boardPosition, Board * _board);
		virtual vector<int> * GetPossibleMoves();
		virtual vector<int> * GetPossibleMoves(bool includeKing);
		virtual Piece * CopyTo(Board * _board);
	};
}

#endif
