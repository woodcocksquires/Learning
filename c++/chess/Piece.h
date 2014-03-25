#ifndef CHESS_PIECE
#define CHESS_PIECE

#include "chess.h"
#include "board.h"
#include <vector>

using namespace std;

namespace Chess {
	class Piece {
		int value;
		string name;
		string shortName;
	  protected:
		bool taken;
		vector<int> * GetOffsetMoves(int distance, bool diagonal);
		vector<int> * GetMultiDirectionMoves(int distance);
		int boardPosition;
		Colour colour;
		Board * board;

		template <class T>
		static Piece * MakePiece(Piece * _piece, Board * _board);
	  public:
		Piece(int _value, Colour _colour, const string _name, const char _shortName, int _boardPosition, Board * _board);
		virtual ~Piece() = 0;
		Piece(const Piece& _piece);
		int GetValue();
		string GetName();
		string GetShortName();
		void SetBoardPosition(int _boardPosition);
		void SetTaken();
		bool GetTaken();
		int GetBoardPosition();
		Colour GetColour();

		virtual vector<int> * GetPossibleMoves() = 0;
		virtual Piece * CopyTo(Board * _board) = 0;
	};
}

#endif
