#ifndef CHESS_BOARD
#define CHESS_BOARD

#include "piece.h"

using namespace Chess;

namespace Chess {
	class Board {
		Piece ** whitePieces, ** blackPieces, ** squares;
		int GetBoardPosition(int row, int col);
	  public:
		Board();
		~Board();
		void InitPieces();
		void InitColourPieces(Piece ** pPieces, Colour colour);
        void ResetBoard();
        Piece * PieceAtPosition(int row, int col);

		template <class T>
		T * MakePiece(Colour colour);

	};
}

#endif
