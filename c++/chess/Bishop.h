#ifndef CHESS_PIECE_BISHOP
#define CHESS_PIECE_BISHOP

#include "chess.h"
#include "piece.h"
#include "board.h"
#include <vector>

using namespace std;

namespace Chess {
	class Bishop: public Piece {
	  public:
		Bishop(Colour _colour, int _boardPosition, Board * _board);
		virtual vector<int> * GetPossibleMoves();
	};
}

#endif
