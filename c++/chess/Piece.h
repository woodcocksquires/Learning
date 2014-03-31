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
		vector<int> * GetOffsetMoves(int distance, bool diagonal, bool includeKing);
		vector<int> * GetMultiDirectionMoves(int distance, bool includeKing);
		int boardPosition;
		Colour colour;
		bool taken;
		bool moved;
		Board * board;


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
		bool HasMoved();
		int GetBoardPosition();
		Colour GetColour();

		virtual vector<int> * GetPossibleMoves() = 0;
		virtual vector<int> * GetPossibleMoves(bool includeKing) = 0;
		virtual Piece * CopyTo(Board * _board) = 0;

		template <class T>
		Piece * MakePiece(T * _piece, Board * _board){
			Piece * piece = new T(_piece->GetColour(), _piece->GetBoardPosition(), _board);
			if(_piece->GetTaken()){
				piece->SetTaken();
			}
			return piece;
		};

	};
}

#endif
