#include "board.h"
#include "chesspieces.h"
#include "chessutils.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include <sstream>

using namespace Chess;
using namespace std;

Board::Board(): movesSincePieceTaken(0) {
	whitePieces = new Piece*[PIECE_COUNT];
	blackPieces = new Piece*[PIECE_COUNT];
	lastMovePiece = nullptr;
	squares = new Piece*[SQUARE_COUNT];
	whiteKing = blackKing = nullptr;

	for(int s=0; s<SQUARE_COUNT; s++){
		squares[s] = nullptr;
	}

	InitPieces();
}

Board::~Board() {
	lastMovePiece = nullptr;
    for(int s=0; s<SQUARE_COUNT; s++){
		squares[s] = nullptr;
	}

    for(int p=0; p<PIECE_COUNT; p++)
    {
        delete whitePieces[p];
        delete blackPieces[p];
        whitePieces[p] = blackPieces[p] = nullptr;
    }

    for(int k=0; k<(int)moveKeys.size(); k++){
    	pair<char*, int>& moveKey = moveKeys[k];
    	delete moveKey.first;
    }

    delete[] whitePieces;
    delete[] blackPieces;
    delete[] squares;
    whitePieces = blackPieces = squares = nullptr;
    whiteKing = blackKing = nullptr;
}

Board::Board(const Board& _board){
	whitePieces = new Piece*[PIECE_COUNT];
	blackPieces = new Piece*[PIECE_COUNT];
	squares = new Piece*[SQUARE_COUNT];
	lastMovePiece = nullptr;
	movesSincePieceTaken = _board.movesSincePieceTaken;

	for(int s=0; s<SQUARE_COUNT; s++){
		squares[s] = nullptr;
	}

	for(int p=0; p<PIECE_COUNT; p++){
		whitePieces[p] = nullptr;
		blackPieces[p] = nullptr;
	}

	for(int p=0; p<PIECE_COUNT; p++){
		whitePieces[p] = _board.whitePieces[p]->CopyTo(this);
		blackPieces[p] = _board.blackPieces[p]->CopyTo(this);
	}

	whiteKing = whitePieces[15];
	blackKing = blackPieces[15];
}

void Board::ResetBoard() {

}

void Board::InitPieces() {
	for(int p=0; p<PIECE_COUNT; p++){
		whitePieces[p] = nullptr;
		blackPieces[p] = nullptr;
	}

	InitColourPieces(whitePieces, Colour::White);
	InitColourPieces(blackPieces, Colour::Black);
}

void Board::InitColourPieces(Piece ** pPieces, Colour colour){
    int modifier = (colour == Colour::White) ? ROW_MODIFIER_WHITE : ROW_MODIFIER_BLACK;
    int baseRow = (colour == Colour::White) ? WHITE_BASE_ROW : BLACK_BASE_ROW;
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
    if(squareReference < MIN_SQUARE_POSITION || squareReference > MAX_SQUARE_POSITION){
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

pair<Move *, MovePieceResult> Board::MovePiece(int startBoardPosition, int endBoardPosition){
    Piece * piece = PieceAtPosition(startBoardPosition);
    Colour opponentColour = (piece->GetColour() == Colour::White ? Colour::Black : Colour::White);
    vector<int> * possibleMoves = piece->GetPossibleMoves();
    Move * move;
    pair<Move *, MovePieceResult> movePair;
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
		move = new Move(startBoardPosition, endBoardPosition, false, movingPiece->GetIdentifier(), movingPiece->GetColour());

		if(dynamic_cast<King*>(movingPiece) != nullptr && abs(startBoardPosition - endBoardPosition)==2){
			bool queenSide = endBoardPosition < startBoardPosition;
			squares[endBoardPosition] = movingPiece;
			movingPiece->SetBoardPosition(endBoardPosition);
			squares[startBoardPosition] = nullptr;
			int rookStartPosition = startBoardPosition + (queenSide ? QUEEN_SIDE_ROOK_OFFSET : KING_SIDE_ROOK_OFFSET);
			int rookEndPosition = endBoardPosition + (queenSide ? KING_SIDE_OFFSET : QUEEN_SIDE_OFFSET);
			Piece * rook = PieceAtPosition(rookStartPosition);
			squares[rookEndPosition] = rook;
			rook->SetBoardPosition(rookEndPosition);

			MovePieceResult moveResult;
			if(TestCheck(opponentColour)){
				moveResult = MovePieceResult::Check;
			}
			else {
				moveResult = MovePieceResult::OK;
			}

			squares[rookStartPosition] = nullptr;
			move->SetIsCastleMove(queenSide);
			move->SetKingChecked(moveResult == MovePieceResult::Check);
			movePair = make_pair(move, moveResult);
			movesSincePieceTaken++;
			return movePair;
		}

		Board moveBoard = Board(*this);
		MovePieceResult testMoveResult = moveBoard.TestLegalMove(startBoardPosition, endBoardPosition);
		if(testMoveResult == MovePieceResult::OK){;
			if(takenPiece != nullptr){
				takenPiece->SetBoardPosition(-1);
				takenPiece->SetTaken();
				move->SetTaken();
				movesSincePieceTaken = 0;
			}
			else if(movingPiece->GetIdentifier() == 'P'){
				movesSincePieceTaken = 0;
			}
			else{
				movesSincePieceTaken++;
			}

			squares[endBoardPosition] = movingPiece;
			movingPiece->SetBoardPosition(endBoardPosition);
			squares[startBoardPosition] = nullptr;

			lastMovePiece = movingPiece;

			if(dynamic_cast<Pawn *>(movingPiece) != nullptr &&
					((movingPiece->GetColour() == Colour::White && ((int)(movingPiece->GetBoardPosition()/8)==BLACK_BASE_ROW)) ||
					(movingPiece->GetColour() == Colour::Black && ((int)(movingPiece->GetBoardPosition()/8)==WHITE_BASE_ROW)))){
				movePair = make_pair(move, MovePieceResult::Promote);
				return movePair;
			}


			MovePieceResult moveResult;
			if(TestCheck(opponentColour)){
				moveResult = MovePieceResult::Check;
				move->SetKingChecked(true);
			}
			else {
				moveResult = MovePieceResult::OK;
			}



			if(AddMoveKey(MakeMoveKey()) == MovePieceResult::RepeatDraw){
				moveResult = MovePieceResult::RepeatDraw;
			}

			if(movesSincePieceTaken == 100){
				moveResult = MovePieceResult::MoveDraw;
			}

			if(IsMaterialDraw()){
				moveResult = MovePieceResult::MaterialDraw;
			}

			movePair = make_pair(move, moveResult);

			return movePair;
		}

		movePair = make_pair(nullptr, testMoveResult);
		return movePair;
	}

	movePair = make_pair(nullptr, MovePieceResult::InvalidMove);
	return movePair;
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
	if(piece->GetBoardPosition() >= 0){
		squares[piece->GetBoardPosition()] = piece;
	}
}

MovePieceResult Board::TestLegalMove(int startBoardPosition, int endBoardPosition){
	Piece * piece = PieceAtPosition(startBoardPosition);
	Piece * takenPiece = PieceAtPosition(endBoardPosition);
	if(takenPiece != nullptr){
		takenPiece->SetBoardPosition(BOARD_POSITION_NOT_ON_BOARD);
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

	for(int p=0; p<PIECE_COUNT; p++){


		Piece * oppositionPiece = oppositionPieces[p];
		if(oppositionPiece->GetTaken() || dynamic_cast<King*>(oppositionPiece) != nullptr){
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
	for(int p=0; p < PIECE_COUNT; p++){
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
	int offset = (queenSide ? QUEEN_SIDE_OFFSET : KING_SIDE_OFFSET);
	int kingPosition = king->GetBoardPosition();
	Rook * rook = (Rook *)PieceAtPosition(kingPosition + (queenSide ? QUEEN_SIDE_ROOK_OFFSET : KING_SIDE_ROOK_OFFSET));

	if(king->HasMoved() || king->GetChecked()){
		return false;
	}

	if(PieceAtPosition(kingPosition + offset) != nullptr
			|| PieceAtPosition(kingPosition + (offset * KING_CASTLE_SQUARES)) != nullptr){
		return false;
	}

	if(queenSide && PieceAtPosition(kingPosition + (offset * QUEEN_CASTLE_SQUARES)) != nullptr){
		return false;
	}

	if(rook == nullptr || rook->HasMoved()){
		return false;
	}

	Board board = Board(*this);
	if(board.TestLegalMove(kingPosition, kingPosition + offset) != MovePieceResult::OK){
		return false;
	}

	if(board.TestLegalMove(kingPosition + offset, kingPosition + (KING_CASTLE_SQUARES * offset)) != MovePieceResult::OK){
		return false;
	}

	return true;
}

void Board::PromotePiece(Piece * piece){
	squares[lastMovePiece->GetBoardPosition()] = piece;
	piece->SetBoardPosition(lastMovePiece->GetBoardPosition());
	Piece ** pieces = (lastMovePiece->GetColour() == Colour::White ? whitePieces : blackPieces);
	for(int p=0; p<PIECE_COUNT; p++){
		if(pieces[p] == lastMovePiece){
			pieces[p] = piece;
			break;
		}
	}
	delete lastMovePiece;
	lastMovePiece = piece;
}

string Board::GetBoardPosition(int boardPosition){
	int row = (boardPosition / 8) + 1;
	int col = boardPosition % 8;

	stringstream ss;
	ss << Utility::ColumnNames[col] << char(row+48);
	return ss.str();
}

char * Board::MakeMoveKey(){
	char * boardString = new char[65];

	for(int s=0; s<64; s++){
		Piece * piece = squares[s];
		if(piece == nullptr){
			boardString[s] = '0';
			continue;
		}
		boardString[64] = '\0';
		char identifier = piece->GetIdentifier();
		boardString[s] = (piece->GetColour() == Colour::White ? identifier : identifier + 32);
	}

	return boardString;
}

MovePieceResult Board::AddMoveKey(char * moveKey){
	for(int k=0; k<(int)moveKeys.size(); k++){
		pair<char *, int>& moveKeyPair = moveKeys[k];
		if(string(moveKey) == string(moveKeyPair.first)){
			if(moveKeyPair.second == 2){
				return MovePieceResult::RepeatDraw;
			}

			moveKeyPair.second = moveKeyPair.second + 1;
			return MovePieceResult::OK;
		}
	}

	moveKeys.push_back(make_pair(moveKey, 1));
	return MovePieceResult::OK;
}

bool Board::IsMaterialDraw(){
	int whiteKnights, blackKnights;
	whiteKnights = blackKnights = 0;
	bool whiteBlackBishop, whiteWhiteBishop, blackBlackBishop, blackWhiteBishop;
	whiteBlackBishop = whiteWhiteBishop = blackBlackBishop = blackWhiteBishop = false;
	bool otherPieces = false;

	for(int p=0; p<15; p++){
		if((!whitePieces[p]->GetTaken() && whitePieces[p]->GetIdentifier() != 'B' && whitePieces[p]->GetIdentifier() != 'N') ||
			(!blackPieces[p]->GetTaken() && blackPieces[p]->GetIdentifier() != 'B' && blackPieces[p]->GetIdentifier() != 'N')){
			otherPieces = true;
			break;
		}

		if(whitePieces[p]->GetIdentifier() == 'N' && !whitePieces[p]->GetTaken()){
			whiteKnights++;
		}

		if(blackPieces[p]->GetIdentifier() == 'N' && !blackPieces[p]->GetTaken()){
			blackKnights++;
		}

		if(whitePieces[p]->GetIdentifier() == 'B' && !whitePieces[p]->GetTaken()){
			if(GetSquareColour(whitePieces[p]->GetBoardPosition()) == Colour::White){
				whiteWhiteBishop = true;
			}
			else{
				whiteBlackBishop = true;
			}
		}

		if(blackPieces[p]->GetIdentifier() == 'B' && !blackPieces[p]->GetTaken()){
			if(GetSquareColour(blackPieces[p]->GetBoardPosition()) == Colour::White){
				whiteWhiteBishop = true;
			}
			else{
				whiteBlackBishop = true;
			}
		}
	}

	if(otherPieces){
		return false;
	}

	if((whiteWhiteBishop && whiteBlackBishop) || (blackWhiteBishop && blackBlackBishop)){
		return false;
	}

	if((whiteKnights > 0 && (whiteWhiteBishop || whiteBlackBishop)) ||
		(blackKnights > 0 && (blackWhiteBishop || blackBlackBishop))){
		return false;
	}

	return true;
}


Colour Board::GetSquareColour(int squarePosition){
    return GetSquareColour(squarePosition / 8, squarePosition % 8);
}

Colour Board::GetSquareColour(int rowOffset, int colOffset){
    return (((rowOffset % 2) + (colOffset % 2)) % 2 == 0) ? Colour::White : Colour::Black;
}
