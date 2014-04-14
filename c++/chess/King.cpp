#include "chess.h"
#include "piece.h"
#include "king.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace Chess;

King::King(Colour _colour, int _boardPosition, Board * _board):
		Piece(0, _colour, "King", 'K', _boardPosition, _board), checked(false) {}

vector<int> * King::GetPossibleMoves(){
	return GetPossibleMoves(false);
}

vector<int> * King::GetPossibleMoves(bool includeKing){
	vector<int> * moves = GetMultiDirectionMoves(1, includeKing);
	vector<int> * outputMoves = new vector<int>();
	if(board->TestCastlingMove(colour, false)){
		moves->push_back((colour == Colour::White ? 6 : 62));
	}

	if(board->TestCastlingMove(colour, true)){
		moves->push_back((colour == Colour::White ? 2 : 58));
	}

	for(int m=0; m<(int)moves->size(); m++){
		int moveRow, moveCol, currentMove;
		currentMove = moves->at(m);
		moveRow = currentMove / 8;
		moveCol = currentMove % 8;
		bool validMove = true;
		for(int t=0; t<8; t++){
			int offsetPosition = 0;
			switch(t){
				case 0:
					offsetPosition = ((moveRow+1)*8)+(moveCol-1);
					break;
				case 1:
					offsetPosition = ((moveRow+1)*8)+moveCol;
					break;
				case 2:
					offsetPosition = ((moveRow+1)*8)+(moveCol+1);
					break;
				case 3:
					offsetPosition = (moveRow*8)+(moveCol-1);
					break;
				case 4:
					offsetPosition = (moveRow*8)+(moveCol+1);
					break;
				case 5:
					offsetPosition = ((moveRow-1)*8)+(moveCol-1);
					break;
				case 6:
					offsetPosition = ((moveRow-1)*8)+moveCol;
					break;
				case 7:
					offsetPosition = ((moveRow-1)*8)+(moveCol+1);
					break;
			}

			if(offsetPosition > 0 && offsetPosition < 64){
				Piece * piece = board->PieceAtPosition(offsetPosition);
				if(piece != nullptr && piece->GetColour() != colour && dynamic_cast<King*>(piece) != nullptr){
					validMove = false;
					break;
				}
			}
		}

		if(validMove){
			outputMoves->push_back(moves->at(m));
		}
	}
	delete moves;

	return outputMoves;
}

Piece * King::CopyTo(Board * _board){
	Piece * piece = Piece::MakePiece<King>(this, _board);
	_board->SetPieceAtPosition(piece);
	return piece;
}

void King::SetChecked(bool value){
	checked = value;
}

bool King::GetChecked(){
	return checked;
}
