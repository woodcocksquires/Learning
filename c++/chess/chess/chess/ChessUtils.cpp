#include "ChessUtils.h"
#include "literals.h"


using namespace Chess;

void Utility::InitialisePieces(Piece ** pPieces, Colour colour){
	pPieces[0] = new Pawn(colour);
	pPieces[1] = new Pawn(colour);
	pPieces[2] = new Pawn(colour);
	pPieces[3] = new Pawn(colour);
	pPieces[4] = new Pawn(colour);
	pPieces[5] = new Pawn(colour);
	pPieces[6] = new Pawn(colour);
	pPieces[7] = new Pawn(colour);
	pPieces[8] = new Knight(colour);
	pPieces[9] = new Knight(colour);
	pPieces[10] = new Rook(colour);
	pPieces[11] = new Rook(colour);
	pPieces[12] = new Bishop(colour);
	pPieces[13] = new Bishop(colour);
	pPieces[14] = new Queen(colour);
	pPieces[15] = new King(colour);
	return;
}

const char * const Utility::ColourStrings[2] { "White", "Black" };
