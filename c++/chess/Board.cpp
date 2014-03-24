#include "board.h"
#include "chesspieces.h"
#include "chessutils.h"
#include <iostream>
#include <vector>

using namespace Chess;
using namespace std;

Board::Board() {
	whitePieces = new Piece*[16];
	blackPieces = new Piece*[16];
	squares = new Piece*[64];

	for(int s=0; s<64; s++){
		squares[s] = nullptr;
	}

	InitPieces();
}

Board::~Board() {
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
}

template <class T>
T * Board::MakePiece(Colour colour, int boardPosition){
	T * pPiece = new T(colour, boardPosition, this);
	return pPiece;
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

	cout << endl;
	for(int m = 0; m < (int)possibleMoves->size(); m++){
		cout << possibleMoves->at(m) << " ";
		if(possibleMoves->at(m) == endBoardPosition){
			possibleMove = true;
		}
	}
	cout << endl;
	delete possibleMoves;

	if(possibleMove){
		Piece * movingPiece = squares[startBoardPosition];
		Piece * takenPiece = squares[endBoardPosition];

		if(takenPiece != nullptr){
			takenPiece->SetBoardPosition(-1);
			takenPiece->SetTaken();
		}

		squares[endBoardPosition] = movingPiece;
		movingPiece->SetBoardPosition(endBoardPosition);
		squares[startBoardPosition] = nullptr;
		return MovePieceResult::OK;
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
