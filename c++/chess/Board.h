#ifndef CHESS_BOARD
#define CHESS_BOARD

#include "piece.h"
#include "move.h"

using namespace Chess;

namespace Chess {
    class Board {
		Piece ** whitePieces, ** blackPieces, ** squares;
		Piece * whiteKing, * blackKing;
		Piece * lastMovePiece;
		static int GetColumn(char columnChar);
      protected:
		MovePieceResult TestLegalMove(int startBoardPosition, int endBoardPosition);
	  public:
		Board();
		~Board();
		Board(const Board& _board);
		void InitPieces();
		void InitColourPieces(Piece ** pPieces, Colour colour);
        void ResetBoard();
        bool TestCastlingMove(Colour colour, bool queenSide);
        bool TestCheck(Colour colour);
        Piece * PieceAtPosition(int row, int col);
        Piece * PieceAtPosition(int squareReference);
        MovePieceResult MovePiece(int startBoardPosition, int endBoardPosition);
        int GetBoardPosition(string squareReference);
        int GetBoardPosition(int row, int col);
        void SetPieceAtPosition(Piece * piece);
        bool TestPlayerHasMoves(Colour colour);
        Piece * GetKing(Colour colour);
        void PromotePiece(Piece * piece);
        template <class T>
        T * MakePiece(Colour colour, int boardPosition){
        	T * pPiece = new T(colour, boardPosition, this);
        	return pPiece;
        }
	};
}

#endif
