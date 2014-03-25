#include "chess.h"
#include "piece.h"
#include "ChessUtils.h"
#include "board.h"
#include <string>
#include <vector>

using namespace std;
using namespace Chess;

Piece::Piece(int _value, Colour _colour, const string _name, const char _shortName, int _boardPosition, Board * _board):
    value(_value), name(_name), boardPosition(_boardPosition), colour(_colour), board(_board), taken(false) {
    shortName = Utility::ColourStrings[colour][0];
    shortName += _shortName;
}

Piece::~Piece(){}

int Piece::GetValue(){
	return value;
}

string Piece::GetName(){
    return name;
}

string Piece::GetShortName(){
    return shortName;
}

Colour Piece::GetColour(){
	return colour;
}

int Piece::GetBoardPosition(){
	return boardPosition;
}

vector<int> * Piece::GetOffsetMoves(int distance, bool diagonal){
	vector<int> * moves = new vector<int>();

	for(int d=0; d<4; d++){
		int row = (int)(boardPosition / 8);
		int col = boardPosition % 8;
		int rowOffset, colOffset;
		int totalOffset = 0;
		switch(d){
			case 0:
				rowOffset = 1;
				colOffset = diagonal ? -1 : 0;
				break;
			case 1:
				rowOffset = diagonal ? 1 : 0;
				colOffset = 1;
				break;
			case 2:
				rowOffset = diagonal ? -1 : 0;
				colOffset = -1;
				break;
			case 3:
				rowOffset = -1;
				colOffset = diagonal ? 1 : 0;
				break;
		}

		while(row >= 0 && row <=7 && col >= 0 && col <= 7 && (totalOffset < distance || distance == -1)){
			row += rowOffset;
			col += colOffset;

			if(row < 0 || row > 7 || col < 0 || col > 7){
				break;
			}

			totalOffset++;
			Piece * piece = board->PieceAtPosition(row, col);

			if(piece == nullptr){
				moves->push_back(board->GetBoardPosition(row, col));
				continue;
			}
			else if(piece->GetColour() != colour && dynamic_cast<King*>(piece) == nullptr){
				moves->push_back(board->GetBoardPosition(row, col));
			}
			else{
				break;
			}
		}
	}

	return moves;
}

vector<int> * Piece::GetMultiDirectionMoves(int distance){
	vector<int> * diagonalMoves, * rankFileMoves;
	diagonalMoves = GetOffsetMoves(distance, true);
	rankFileMoves = GetOffsetMoves(distance, false);
	vector<int> * moves = new vector<int>();
	moves->reserve(diagonalMoves->size() + rankFileMoves->size());
	moves->insert(moves->end(), diagonalMoves->begin(), diagonalMoves->end());
	moves->insert(moves->end(), rankFileMoves->begin(), rankFileMoves->end());
	delete diagonalMoves;
	delete rankFileMoves;
	return moves;
}

void Piece::SetBoardPosition(int _boardPosition){
	boardPosition = _boardPosition;
}

void Piece::SetTaken(){
	taken = true;
}

bool Piece::GetTaken(){
	return taken;
}

template <class T>
Piece * Piece::MakePiece(Piece * _piece, Board * _board){
	Piece * piece = new T(_piece->GetColour(), piece->GetBoardPosition(), _board);
	_board->SetPieceAtPosition(piece, _piece->GetBoardPosition());
	if(_piece->GetTaken()){
		piece->SetTaken();
	}
	return piece;
}
