#include "board.h"
#include "chesspieces.h"
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
	cout << "deconstructing..." << endl;
}

void Board::ResetBoard() {

}

void Board::InitPieces() {
	for(int p=0; p<16; p++){
		whitePieces[p] = nullptr;
		blackPieces[p] = nullptr;
	}

	InitColourPieces(whitePieces, PieceColour::White);
	InitColourPieces(whitePieces, PieceColour::Black);
}

void Board::InitColourPieces(Piece ** pPieces, PieceColour colour){
	pPieces[0] = MakePiece<Pawn>(colour);
	pPieces[1] = MakePiece<Pawn>(colour);
	pPieces[2] = MakePiece<Pawn>(colour);
	pPieces[3] = MakePiece<Pawn>(colour);
	pPieces[4] = MakePiece<Pawn>(colour);
	pPieces[5] = MakePiece<Pawn>(colour);
	pPieces[6] = MakePiece<Pawn>(colour);
	pPieces[7] = MakePiece<Pawn>(colour);
	pPieces[8] = MakePiece<Knight>(colour);
	pPieces[9] = MakePiece<Knight>(colour);
	pPieces[10] = MakePiece<Rook>(colour);
	pPieces[11] = MakePiece<Rook>(colour);
	pPieces[12] = MakePiece<Bishop>(colour);
	pPieces[13] = MakePiece<Bishop>(colour);
	pPieces[14] = MakePiece<Queen>(colour);
	pPieces[15] = MakePiece<King>(colour);
}

template <class T>
T * Board::MakePiece(PieceColour colour){
	T * pPiece = new T(colour);
	cout << "Made new " << PieceColourStrings[colour] << " " << pPiece->GetName() << endl;
	return pPiece;
}
