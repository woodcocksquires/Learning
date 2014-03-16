#include "board.h"
#include "chesspieces.h"
#include "chessutils.h"
#include <iostream>

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
        pPieces[p] = MakePiece<Pawn>(colour);
        squares[GetBoardPosition(baseRow+modifier,p)] = pPieces[p];
	}
	pPieces[8] = MakePiece<Knight>(colour);
	squares[GetBoardPosition(baseRow,1)] = pPieces[8];
	pPieces[9] = MakePiece<Knight>(colour);
	squares[GetBoardPosition(baseRow,6)] = pPieces[9];
	pPieces[10] = MakePiece<Rook>(colour);
	squares[GetBoardPosition(baseRow,0)] = pPieces[10];
	pPieces[11] = MakePiece<Rook>(colour);
	squares[GetBoardPosition(baseRow,7)] = pPieces[11];
	pPieces[12] = MakePiece<Bishop>(colour);
	squares[GetBoardPosition(baseRow,2)] = pPieces[12];
	pPieces[13] = MakePiece<Bishop>(colour);
	squares[GetBoardPosition(baseRow,5)] = pPieces[13];
	pPieces[14] = MakePiece<Queen>(colour);
	squares[GetBoardPosition(baseRow,3)] = pPieces[14];
	pPieces[15] = MakePiece<King>(colour);
	squares[GetBoardPosition(baseRow,4)] = pPieces[15];
}

template <class T>
T * Board::MakePiece(Colour colour){
	T * pPiece = new T(colour);
	//cout << "Made new " << Utility::ColourStrings[colour] << " " << pPiece->GetName() << endl;
	return pPiece;
}

Piece * Board::PieceAtPosition(int row, int col){
    return squares[GetBoardPosition(row, col)];
}

int Board::GetBoardPosition(int row, int col){
    return row*8+col;
}

MovePieceResult Board::MovePiece(Move m){
    Piece * movingPiece = squares[(8*1)+4];
    squares[(8*3)+4] = movingPiece;
    squares[(8*1)+4] = nullptr;
}
