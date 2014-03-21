#ifndef CHESS_PIECE_KING
#define CHESS_PIECE_KING

#include "chess.h"
#include "piece.h"
#include "board.h"
#include <vector>

namespace Chess {
	class King: public Piece {
	  public:
		King(Colour _colour, int _boardPosition, Board * _board);
		vector<int> GetPossibleMoves();
	};
}

#endif