#ifndef CHESS_BOARD
#define CHESS_BOARD

#include "piece.h"

using namespace Chess;

namespace Chess {
	class Board {
		Piece ** whitePieces, ** blackPieces, ** squares;
		void RenderRow(int offset);
	  public:
		Board();
		~Board();
		void InitPieces();
		void InitColourPieces(Piece ** pPieces, PieceColour colour);

		template <class T>
		T * MakePiece(PieceColour colour);
	  	void ResetBoard();
	  	void Render();
	};
}

#endif
