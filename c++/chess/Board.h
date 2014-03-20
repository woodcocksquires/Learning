#ifndef CHESS_BOARD
#define CHESS_BOARD

#include "piece.h"
#include "move.h"

using namespace Chess;

namespace Chess {
    class Board {
		Piece ** whitePieces, ** blackPieces, ** squares;
		template <class T>
		T * MakePiece(Colour colour);
		static int GetColumn(char columnChar);
	  public:
		Board();
		~Board();
		void InitPieces();
		void InitColourPieces(Piece ** pPieces, Colour colour);
        void ResetBoard();
        Piece * PieceAtPosition(int row, int col);
        Piece * PieceAtPosition(int squareReference);
        MovePieceResult MovePiece(int startBoardPosition, int endBoardPosition);
        int GetBoardPosition(string squareReference);
        int GetBoardPosition(int row, int col);
	};
}

#endif
