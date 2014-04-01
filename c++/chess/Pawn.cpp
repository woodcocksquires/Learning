#include "chess.h"
#include "piece.h"
#include "board.h"
#include "pawn.h"
#include "king.h"
#include <string>
#include <vector>

using namespace std;
using namespace Chess;

Pawn::Pawn(Colour _colour, int _boardPosition, Board * _board):
		Piece(1, _colour, "Pawn", 'P', _boardPosition, _board) {}

vector<int> * Pawn::GetPossibleMoves(){
	return GetPossibleMoves(false);
}

vector<int> * Pawn::GetPossibleMoves(bool includeKing){
	vector<int> * moves = new vector<int>();
	int row = (int)(boardPosition / 8);
	int col = boardPosition % 8;
	int offset = (colour == Colour::White ? 1 : -1);

	if((colour == Colour::White && row == 1) || (colour == Colour::Black && row == 6)){
		if(board->PieceAtPosition(row+ (2*offset), col) == nullptr){
			moves->push_back(board->GetBoardPosition(row + (2*offset), col));
		}

		if(col > 0){
			Piece * piece = board->PieceAtPosition(row + (2*offset), col-1);
			if(piece != nullptr && piece->GetColour() != colour && (dynamic_cast<King*>(piece) == nullptr || includeKing)){
				moves->push_back(board->GetBoardPosition(row + (2*offset), col - 1));
			}
		}

		if(col < 7){
			Piece * piece = board->PieceAtPosition(row + (2*offset), col+1);
			if(piece != nullptr && piece->GetColour() != colour && (dynamic_cast<King*>(piece) == nullptr || includeKing)){
				moves->push_back(board->GetBoardPosition(row + (2*offset), col + 1));
			}
		}

	}

	if((row + offset) <= 7 && (row + offset) >= 0){
		if(board->PieceAtPosition(row + offset, col) == nullptr){
			moves->push_back(board->GetBoardPosition(row + offset, col));
		}

		if(col > 0){
			Piece * piece = board->PieceAtPosition(row + offset, col-1);
			if(piece != nullptr && piece->GetColour() != colour
					&& (dynamic_cast<King*>(piece) == nullptr || includeKing)
					&& dynamic_cast<Pawn*>(piece) != nullptr){
				moves->push_back(board->GetBoardPosition(row + offset, col - 1));
			}
		}

		if(col < 7){
			Piece * piece = board->PieceAtPosition(row + offset, col+1);
			if(piece != nullptr && piece->GetColour() != colour
					&& (dynamic_cast<King*>(piece) == nullptr || includeKing)
					&& dynamic_cast<Pawn*>(piece) != nullptr){
				moves->push_back(board->GetBoardPosition(row + offset, col + 1));
			}
		}
	}

	return moves;
}

Piece * Pawn::CopyTo(Board * _board){
	Piece * piece = Piece::MakePiece<Pawn>(this, _board);
	_board->SetPieceAtPosition(piece);
	return piece;
}
