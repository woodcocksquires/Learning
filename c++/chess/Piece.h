#ifndef CHESS_PIECE
#define CHESS_PIECE

#include "chess.h"
#include <vector>

using namespace std;

namespace Chess {
	class Piece {
		int value;
		Colour colour;
		string name;
		string shortName;
		int boardPosition;
		Board * board;
	  protected:
		vector<int> * GetOffsetMoves(int distance, bool diagonal);
		vector<int> * GetMultiDirectionMoves(int distance);
	  public:
		Piece(int _value, Colour _colour, const string _name, const char _shortName, int _boardPosition, Board * _board);
		int GetValue();
		string GetName();
		string GetShortName();
		virtual vector<int> GetPossibleMoves() = 0;
		Colour GetColour();
	};
}

#endif
