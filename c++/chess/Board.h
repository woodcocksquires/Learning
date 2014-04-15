#ifndef CHESS_BOARD
#define CHESS_BOARD

#include <utility>
#include "piece.h"
#include "move.h"
#include <vector>

using namespace std;
using namespace Chess;

namespace Chess {
    class Board {
		Piece ** whitePieces, ** blackPieces, ** squares;
		Piece * whiteKing, * blackKing;
		Piece * lastMovePiece;
		vector<pair<char*, int>> moveKeys;
		static int GetColumn(char columnChar);
		char * MakeMoveKey();
		MovePieceResult AddMoveKey(char * moveKey);
		bool IsMaterialDraw();
		int movesSincePieceTaken;
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
        pair<Move *, MovePieceResult> MovePiece(int startBoardPosition, int endBoardPosition);
        int GetBoardPosition(string squareReference);
        int GetBoardPosition(int row, int col);
        static string GetBoardPosition(int boardPosition);
        void SetPieceAtPosition(Piece * piece);
        bool TestPlayerHasMoves(Colour colour);
        Piece * GetKing(Colour colour);
        void PromotePiece(Piece * piece);
        MovePieceResult TestLegalMove(int startBoardPosition, int endBoardPosition);
        template <class T>
        T * MakePiece(Colour colour, int boardPosition){
        	T * pPiece = new T(colour, boardPosition, this);
        	return pPiece;
        }
        Colour GetSquareColour(int row, int col);
        Colour GetSquareColour(int boardPosition);
	};
}

#endif
