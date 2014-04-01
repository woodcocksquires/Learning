#include "board.h"
#include "chesspieces.h"
#include "chessutils.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace Chess;
using namespace std;

Board::Board() {
	whitePieces = new Piece*[16];
	blackPieces = new Piece*[16];
	lastMovePiece = nullptr;
	squares = new Piece*[64];
	whiteKing = blackKing = nullptr;

	for(int s=0; s<64; s++){
		squares[s] = nullptr;
	}

	InitPieces();
}

Board::~Board() {
	lastMovePiece = nullptr;
    for(int s=0; s<64; s++){
		squares[s] = nullptr;
	}

    for(int p=0; p<16; p++)
    {
        delete whitePieces[p];
        delete blackPieces[p];
        whitePieces[p] = blackPieces[p] = nullptr;
    }

    delete[] whitePieces;
    delete[] blackPieces;
    delete[] squares;
    whitePieces = blackPieces = squares = nullptr;
    whiteKing = blackKing = nullptr;
}

Board::Board(const Board& _board){
	whitePieces = new Piece*[16];
	blackPieces = new Piece*[16];
	squares = new Piece*[64];
	lastMovePiece = nullptr;

	for(int s=0; s<64; s++){
		squares[s] = nullptr;
	}

	for(int p=0; p<16; p++){
		whitePieces[p] = nullptr;
		blackPieces[p] = nullptr;
	}

	for(int p=0; p<16; p++){
		whitePieces[p] = _board.whitePieces[p]->CopyTo(this);
		blackPieces[p] = _board.blackPieces[p]->CopyTo(this);
	}

	whiteKing = whitePieces[15];
	blackKing = blackPieces[15];
}

void Board::ResetBoard() {

}

void Board::InitPieces() {
	for(int p=0; p<16; p++){
		whitePieces[p] = nullptr;
		blackPieces[p] = nullptr;
	}

	InitColourPieces(whitePieces, Colour::White);
	InitColourPieces(blackPieces, Colour::Black);
}

void Board::InitColourPieces(Piece ** pPieces, Colour colour){
    int modifier = (colour == Colour::White) ? 1 : -1;
    int baseRow = (colour == Colour::White) ? 0 : 7;
	for(int p = 0; p<8; p++){
        pPieces[p] = MakePiece<Pawn>(colour, ((baseRow+modifier)*8)+p);
        squares[GetBoardPosition(baseRow+modifier,p)] = pPieces[p];
	}
	int basePosition = baseRow*8;
	pPieces[8] = MakePiece<Knight>(colour, basePosition + 1);
	squares[GetBoardPosition(baseRow,1)] = pPieces[8];
	pPieces[9] = MakePiece<Knight>(colour, basePosition + 6);
	squares[GetBoardPosition(baseRow,6)] = pPieces[9];
	pPieces[10] = MakePiece<Rook>(colour, basePosition);
	squares[GetBoardPosition(baseRow,0)] = pPieces[10];
	pPieces[11] = MakePiece<Rook>(colour, basePosition + 7);
	squares[GetBoardPosition(baseRow,7)] = pPieces[11];
	pPieces[12] = MakePiece<Bishop>(colour, basePosition + 2);
	squares[GetBoardPosition(baseRow,2)] = pPieces[12];
	pPieces[13] = MakePiece<Bishop>(colour, basePosition + 5);
	squares[GetBoardPosition(baseRow,5)] = pPieces[13];
	pPieces[14] = MakePiece<Queen>(colour, basePosition + 3);
	squares[GetBoardPosition(baseRow,3)] = pPieces[14];
	pPieces[15] = MakePiece<King>(colour, basePosition + 4);
	squares[GetBoardPosition(baseRow,4)] = pPieces[15];
	if(colour == Colour::White){
		whiteKing = pPieces[15];
	}
	else{
		blackKing = pPieces[15];
	}
}

Piece * Board::PieceAtPosition(int row, int col){
    return squares[GetBoardPosition(row, col)];
}

Piece * Board::PieceAtPosition(int squareReference){
    if(squareReference < 0 || squareReference > 63){
        return nullptr;
    }

    return squares[squareReference];
}

int Board::GetBoardPosition(int row, int col){
    return row*8+col;
}

int Board::GetBoardPosition(string squareReference){
    if(squareReference.length() != 2){
        return -1;
    }

    char firstChar, secondChar;
    firstChar = squareReference[0];
    secondChar = squareReference[1];
    int column = Board::GetColumn(firstChar);

    if(column == -1 || secondChar < 49 || secondChar > 56){
        return -1;
    }

    return ((((int)secondChar)-48-1)*8) + column;
}

MovePieceResult Board::MovePiece(int startBoardPosition, int endBoardPosition){
    Piece * piece = PieceAtPosition(startBoardPosition);
    vector<int> * possibleMoves = piece->GetPossibleMoves();
	bool possibleMove = false;
	for(int m = 0; m < (int)possibleMoves->size(); m++){

		if(possibleMoves->at(m) == endBoardPosition){
			possibleMove = true;
		}
	}
	delete possibleMoves;

	if(possibleMove){
		Piece * movingPiece = squares[startBoardPosition];
		Piece * takenPiece = squares[endBoardPosition];

		if(dynamic_cast<King*>(movingPiece) != nullptr && abs(startBoardPosition - endBoardPosition)==2){
			bool queenSide = endBoardPosition < startBoardPosition;
			squares[endBoardPosition] = movingPiece;
			movingPiece->SetBoardPosition(endBoardPosition);
			squares[startBoardPosition] = nullptr;
			int rookStartPosition = startBoardPosition + (queenSide ? -4 : 3);
			int rookEndPosition = endBoardPosition + (queenSide ? 1 : -1);
			Piece * rook = PieceAtPosition(rookStartPosition);
			squares[rookEndPosition] = rook;
			rook->SetBoardPosition(rookEndPosition);
			squares[rookStartPosition] = nullptr;
			return MovePieceResult::OK;
		}

		Board moveBoard = Board(*this);
		MovePieceResult testMoveResult = moveBoard.TestLegalMove(startBoardPosition, endBoardPosition);
		if(testMoveResult == MovePieceResult::OK){;
			if(takenPiece != nullptr){
				takenPiece->SetBoardPosition(-1);
				takenPiece->SetTaken();
			}

			squares[endBoardPosition] = movingPiece;
			movingPiece->SetBoardPosition(endBoardPosition);
			squares[startBoardPosition] = nullptr;

			lastMovePiece = movingPiece;

			if(dynamic_cast<Pawn *>(movingPiece) != nullptr &&
					((movingPiece->GetColour() == Colour::White && ((int)(movingPiece->GetBoardPosition()/8)==7)) ||
					(movingPiece->GetColour() == Colour::Black && ((int)(movingPiece->GetBoardPosition()/8)==0)))){
				return MovePieceResult::Promote;
			}

			Colour opponentColour = (piece->GetColour() == Colour::White ? Colour::Black : Colour::White);
			if(TestCheck(opponentColour)){
				return MovePieceResult::Check;
			}
			else {
				return MovePieceResult::OK;
			}
		}

		return testMoveResult;
	}

	return MovePieceResult::InvalidMove;
}

int Board::GetColumn(char columnChar){
    if(columnChar > 96){
        columnChar = columnChar - 32;
    }

    for(int r=0; r<8; r++){
        if(Utility::ColumnNames[r] == columnChar){
            return r;
        }
    }

    return -1;
}

void Board::SetPieceAtPosition(Piece * piece){
	squares[piece->GetBoardPosition()] = piece;
}

MovePieceResult Board::TestLegalMove(int startBoardPosition, int endBoardPosition){
	Piece * piece = PieceAtPosition(startBoardPosition);
	Piece * takenPiece = PieceAtPosition(endBoardPosition);
	if(takenPiece != nullptr){
		takenPiece->SetBoardPosition(-1);
		takenPiece->SetTaken();
	}

	squares[endBoardPosition] = piece;
	piece->SetBoardPosition(endBoardPosition);
	squares[startBoardPosition] = nullptr;

	if(TestCheck(piece->GetColour())){
		return MovePieceResult::IllegalMove;
	}

	return MovePieceResult::OK;
}

bool Board::TestCheck(Colour colour){
	Piece ** oppositionPieces;
	Piece * activeKing;
	if(colour == Colour::White){
		oppositionPieces = blackPieces;
		activeKing = whiteKing;
	}
	else{
		oppositionPieces = whitePieces;
		activeKing = blackKing;
	}

	for(int p=0; p<16; p++){
		Piece * oppositionPiece = oppositionPieces[p];
		if(oppositionPiece->GetTaken()){
			continue;
		}

		vector<int> * moves = oppositionPiece->GetPossibleMoves(true);
		for(int m=0; m<(int)moves->size(); m++){
			if(moves->at(m) == activeKing->GetBoardPosition()){
				delete moves;
				return true;
			}
		}
		delete moves;
	}

	return false;
}

bool Board::TestPlayerHasMoves(Colour colour){
	Piece ** pieces = (colour == Colour::White ? whitePieces : blackPieces);
	for(int p=0; p<16; p++){
		Piece * piece = pieces[p];
		if(!piece->GetTaken()){
			vector<int> * moves = piece->GetPossibleMoves();
			for(int m=0; m<(int)moves->size(); m++){
				Board b = Board(*this);
				MovePieceResult r = b.TestLegalMove(piece->GetBoardPosition(), moves->at(m));
				if(r != MovePieceResult::InvalidMove && r != MovePieceResult::IllegalMove){
					delete moves;
					return true;
				}
			}
			delete moves;
		}
	}

	return false;
}

Piece * Board::GetKing(Colour colour){
	return (colour == Colour::White ? whiteKing : blackKing);
}

bool Board::TestCastlingMove(Colour colour, bool queenSide){
	King * king = (King *)(colour == Colour::White ? whiteKing : blackKing);
	int row = (colour == Colour::White ? 0 : 7);
	int offset = (queenSide ? -1 : 1);
	int kingPosition = (row*8) + 4;
	Rook * rook = (Rook *)PieceAtPosition((row*8) + (queenSide ? 0 : 7));

	if(king->HasMoved() || king->GetChecked()){
		return false;
	}

	if(PieceAtPosition(kingPosition + offset) != nullptr
			|| PieceAtPosition(kingPosition + (offset*2)) != nullptr){
		return false;
	}

	if(queenSide && PieceAtPosition(kingPosition + (offset * 3)) != nullptr){
		return false;
	}

	if(rook == nullptr || rook->HasMoved()){
		return false;
	}

	Board board = Board(*this);
	if(board.TestLegalMove(kingPosition, kingPosition + offset) != MovePieceResult::OK){
		return false;
	}

	if(board.TestLegalMove(kingPosition + offset, kingPosition + (2*offset)) != MovePieceResult::OK){
		return false;
	}

	return true;
}

void Board::PromotePiece(Piece * piece){
	squares[lastMovePiece->GetBoardPosition()] = piece;
	piece->SetBoardPosition(lastMovePiece->GetBoardPosition());
	Piece ** pieces = (lastMovePiece->GetColour() == Colour::White ? whitePieces : blackPieces);
	for(int p=0; p<16; p++){
		if(pieces[p] == lastMovePiece){
			pieces[p] = piece;
			break;
		}
	}
	delete lastMovePiece;
	lastMovePiece = piece;
}

