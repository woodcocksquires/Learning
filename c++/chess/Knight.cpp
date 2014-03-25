#include "chess.h"
#include "piece.h"
#include "knight.h"
#include <string>
#include <vector>
#include "king.h"

using namespace std;
using namespace Chess;

Knight::Knight(Colour _colour, int _boardPosition, Board * _board):
		Piece(3, _colour, "Knight", 'N', _boardPosition, _board) {}

vector<int> * Knight::GetPossibleMoves(){
	vector<int> * moves = new vector<int>();
	int row = (int)(boardPosition / 8);
	int col = boardPosition % 8;

	for(int p = 0; p < 8; p++){
		int rowOffset, colOffset;
		switch(p){
			case 0:
				rowOffset = 2;
				colOffset = -1;
				break;
			case 1:
				rowOffset = 2;
				colOffset = 1;
				break;
			case 2:
				rowOffset = 1;
				colOffset = -2;
				break;
			case 3:
				rowOffset = 1;
				colOffset = 2;
				break;
			case 4:
				rowOffset = -1;
				colOffset = -2;
				break;
			case 5:
				rowOffset = -1;
				colOffset = 2;
				break;
			case 6:
				rowOffset = -2;
				colOffset = -1;
				break;
			case 7:
				rowOffset = -2;
				colOffset = 1;
				break;
		}

		if((row + rowOffset) >= 0 && (row + rowOffset) <= 7 && (col + colOffset) >= 0 && (col+colOffset) <= 7){
			Piece * piece = board->PieceAtPosition(row + rowOffset, col + colOffset);
			if(piece == nullptr){
				moves->push_back(board->GetBoardPosition(row + rowOffset, col + colOffset));
			}
			else if(piece->GetColour() != colour && dynamic_cast<King*>(piece) == nullptr){
				moves->push_back(board->GetBoardPosition(row + rowOffset, col + colOffset));
			}
		}
	}

	return moves;
}

Piece * Knight::CopyTo(Board * _board){
	return Piece::MakePiece<Knight>(this, _board);
}
