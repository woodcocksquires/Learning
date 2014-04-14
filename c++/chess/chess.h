#ifndef CHESS
#define CHESS

#include <string>
#include "literals.h"

using namespace std;

namespace Chess {
	class Board;
	class Piece;
	class Move;

	enum Colour: int { White, Black };
	enum PlayerType: int { Human, CPU };
	enum GameStatus: int { Active, Mate, Stalemate, InCheck, Draw, Resigned, DrawRepeated, DrawNoTaken, DrawMaterial };
	enum MovePieceResult: int { OK, InvalidMove, IllegalMove, Check, Promote, OfferDraw, Resign, RepeatDraw, MoveDraw, MaterialDraw };
	const int PIECE_COUNT = 16;
	const int SQUARE_COUNT = 64;
	const int QUEEN_SIDE_ROOK_OFFSET = -4;
	const int KING_SIDE_ROOK_OFFSET = 3;
	const int WHITE_BASE_ROW = 0;
	const int BLACK_BASE_ROW = 7;
	const int QUEEN_SIDE_OFFSET = -1;
	const int KING_SIDE_OFFSET = 1;
	const int KING_CASTLE_SQUARES = 2;
	const int QUEEN_CASTLE_SQUARES = 3;
	const int ROW_MODIFIER_WHITE = 1;
	const int ROW_MODIFIER_BLACK = -1;
	const int MIN_SQUARE_POSITION = 0;
	const int MAX_SQUARE_POSITION = SQUARE_COUNT -1;
	const int BOARD_POSITION_NOT_ON_BOARD = -1;
}

#endif
