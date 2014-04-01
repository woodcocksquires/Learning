#include <iostream>
#include "ConsoleChessRenderer.h"
#include "Board.h"
#include "Chess.h"
#include "ChessPieces.h"
#include "ChessUtils.h"
#include "Move.h"

using namespace Chess::Renderer;
using namespace Chess;

ConsoleChessRenderer::~ConsoleChessRenderer(){}

void ConsoleChessRenderer::RenderBoard(Board * board, bool inverse) {
    if(!inverse){
        for(int r = 7; r>=0; r--){
            RenderBoardRow(board, r, inverse);
        }
    }
    else {
        for(int r = 0; r<8; r++){
            RenderBoardRow(board, r, inverse);
        }
    }
    RenderBoardRowBorder();
    RenderBoardLabelRow(inverse);
    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRow(Board * board, int offset, bool inverse){
    RenderBoardRowBorder();
    RenderBoardRowInner(ConsoleRowInnerType::Surround, board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Spacer, board, offset, inverse);
    RenderBoardRowContent(board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Spacer, board, offset, inverse);
    RenderBoardRowInner(ConsoleRowInnerType::Surround, board, offset, inverse);
}

void ConsoleChessRenderer::RenderBoardRowBorder(){
    cout << "   ";
    for(int c=1; c<=8; c++)
    {
        cout << "+--------";
        if(c==8){
            cout << "+";
        }
    }
    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowInner(ConsoleRowInnerType type, Board * board, int offset, bool inverse){
    switch(type)
    {
        case ConsoleRowInnerType::Surround:
            RenderBoardRowNonContent(offset, inverse, false);
            break;
        case ConsoleRowInnerType::Spacer:
            RenderBoardRowNonContent(offset, inverse, true);
            break;
        case ConsoleRowInnerType::Content:
            RenderBoardRowContent(board, offset, inverse);
            break;
    }
}

void ConsoleChessRenderer::RenderBoardRowNonContent(int offset, bool inverse, bool isSpacer){
    cout << "   ";

    if(!inverse){
        for(int c=0; c<8; c++)
        {
            RenderBoardRowNonContentColumn(offset, c, inverse, isSpacer);
        }
    }
    else{
        for(int c=7; c>=0; c--)
        {
            RenderBoardRowNonContentColumn(offset, c, inverse, isSpacer);
        }
    }

    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowNonContentColumn(int row, int col, bool inverse, bool isSpacer){
    cout << "|";
    Colour squareColour = GetSquareColour(row, col);
    if(squareColour == Colour::Black){
        cout << "        ";
    }
    else{
        cout << "##";
        cout << (isSpacer ? "    " : "####");
        cout << "##";
    }

    if((inverse && col==0 ) || (!inverse && col==7)){
        cout << "|";
    }
}

void ConsoleChessRenderer::RenderBoardRowContent(Board * board, int offset, bool inverse){
    cout << " " << (offset + 1) << " ";

    if(!inverse){
        for(int c=0; c<8; c++)
        {
            RenderBoardRowContentColumn(board, offset, c, inverse);
        }
    }
    else{
        for(int c=7; c>=0; c--)
        {
            RenderBoardRowContentColumn(board, offset, c, inverse);
        }
    }

    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowContentColumn(Board* board, int row, int col, bool inverse){
    cout << "|";
    Colour squareColour = GetSquareColour(row, col);
    Piece * piece = board->PieceAtPosition(row, col);
    if(squareColour == Colour::Black){
        cout << "   ";
        cout << (piece == nullptr ? "  " : piece->GetShortName());
        cout << "   ";
    }
    else{
        cout << "## ";
        cout << (piece == nullptr ? "  ": piece->GetShortName());
        cout << " ##";
    }

    if((inverse && col==0) || (!inverse && col==7)){
        cout << "|";
    }
}

void ConsoleChessRenderer::RenderBoardLabelRow(bool inverse){
    cout << "    ";
    if(!inverse){
        for(int c=0; c<8; c++){
            cout << "   " << Utility::ColumnNames[c] << "     ";
        }
    }
    else{
        for(int c=7; c>=0; c--){
            cout << "   " << Utility::ColumnNames[c] << "     ";
        }
    }
    cout << endl;
}

Colour ConsoleChessRenderer::GetSquareColour(int rowOffset, int colOffset){
    return (((rowOffset % 2) + (colOffset % 2)) % 2 == 0) ? Colour::White : Colour::Black;
}

void ConsoleChessRenderer::StartGame(){
    cout << "Welcome to Console Chess!" << endl << endl << endl;
}

PlayerType ConsoleChessRenderer::GetPlayerType(Colour colour){
    string input = "";
    const char * colourString = Utility::ColourStrings[colour];

    cout << "Please choose type of player for " << colourString << " from the options below. \n";
    cout << "   1   Human\n";
    cout << "   2   CPU\n\n";
    cout << "Option: ";

    cin >> input;

    while(input != "1" && input != "2"){
        input = "";
        cout << endl << "Incorrect input, please try again." << endl;
        cout << "Option: " << flush;
        cin >> input;
    }

    PlayerType output = (PlayerType)((int)input[0] - 48 - 1);
    cout << endl << "Selected player type for " << colourString << " is " << Utility::PlayerTypeStrings[output] << "." << endl << endl;
    return output;
}

MovePieceResult ConsoleChessRenderer::MakeMove(Colour colour, Board * board){
    string startPosition, endPosition;
    int startBoardPosition, endBoardPosition;
    Piece * startPiece = nullptr;
    bool opponentPiece = false;

    cout << endl;
    cout << Utility::ColourStrings[colour] << ", please enter the reference of the piece you would like to move.";
    cout << endl;
    cout << "Reference: " << flush;

    do{
    	opponentPiece = false;
        cin >> startPosition;
        startBoardPosition = board->GetBoardPosition(startPosition);

        if(startBoardPosition == -1){
            cout << endl << "Incorrect reference, please try again. \n Reference: " << flush;
            continue;
        }

        startPiece = board->PieceAtPosition(startBoardPosition);
        if(startPiece == nullptr){
            cout << "\nNo piece at " << startPosition << ", please try again. Reference: " << flush;
        }
        else if(startPiece->GetColour() != colour){
        	opponentPiece = true;
        	cout << "\nPiece at " << startPosition << " is opponent's piece, please try again.  Reference: " << flush;
        }

    }while(startBoardPosition == -1 || startPiece == nullptr || opponentPiece);

    cout << endl << "Please enter the reference of the position you would like to move the piece to.";
    cout << endl << "Reference: " << flush;
    cin >> endPosition;

    endBoardPosition = board->GetBoardPosition(endPosition);
    while(endBoardPosition == -1){
        cout << endl << "Incorrect reference, please try again." << endl << "Reference: " << flush;
        cin >> endPosition;
        endBoardPosition = board->GetBoardPosition(endPosition);
    }

    return board->MovePiece(startBoardPosition, endBoardPosition);
}

void ConsoleChessRenderer::RenderMessage(string message){
	cout << message << endl;
}

void ConsoleChessRenderer::RenderMoves(){

}

void ConsoleChessRenderer::PromotePiece(Colour colour, Board * board){
	cout << "\n" + string(Utility::ColourStrings[colour]) + " please select the piece type to promote to:\n\n";
	cout << "   1   Knight\n   2   Bishop\n   3   Rook\n   4   Queen\n\n";

	int pieceType = 0;
	string input;
	while(pieceType==0){
		cout << "Option: ";
		cin >> input;
		if(input.length() > 1 || input[0] < 49 || input[0] > 52){
			cout << "Invalid input, please try again.\n";
			continue;
		}
		Piece * newPiece;
		switch(((int)input[0])-48){
			case 1:
				newPiece = board->MakePiece<Knight>(colour, 0);
				break;
			case 2:
				newPiece = board->MakePiece<Bishop>(colour, 0);
				break;
			case 3:
				newPiece = board->MakePiece<Rook>(colour, 0);
				break;
			case 4:
				newPiece = board->MakePiece<Queen>(colour, 0);
				break;
		}
		board->PromotePiece(newPiece);
	}
}
