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
		bool taken;
	  protected:
		vector<int> * GetOffsetMoves(int distance, bool diagonal);
		vector<int> * GetMultiDirectionMoves(int distance);
		int boardPosition;
		Colour colour;
		Board * board;
	  public:
		Piece(int _value, Colour _colour, const string _name, const char _shortName, int _boardPosition, Board * _board);
		virtual ~Piece() = 0;
		int GetValue();
		string GetName();
		string GetShortName();
		virtual vector<int> * GetPossibleMoves() = 0;
		void SetBoardPosition(int _boardPosition);
		void SetTaken();
		bool GetTaken();
		Colour GetColour();
	};
}

#endif
