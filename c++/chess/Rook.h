#ifndef CHESS_PIECE_ROOK
#define CHESS_PIECE_ROOK

#include "chess.h"
#include "piece.h"
#include "board.h"
#include <vector>

namespace Chess {
	class Rook: public Piece {
	  public:
		Rook(Colour _colour, int _boardPosition, Board * _board);
		vector<int> * GetPossibleMoves();
	};
}

#endif