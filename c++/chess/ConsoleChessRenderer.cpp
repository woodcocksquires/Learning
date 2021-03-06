#include <iostream>
#include "Chess.h"
#include "ChessPieces.h"
#include "ConsoleChessRenderer.h"
#include "Board.h"
#include "ChessUtils.h"
#include "Move.h"
#include <utility>
#include <sstream>

using namespace Chess::Renderer;
using namespace Chess;
using namespace std;

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
            RenderBoardRowNonContent(offset, inverse, false, board);
            break;
        case ConsoleRowInnerType::Spacer:
            RenderBoardRowNonContent(offset, inverse, true, board);
            break;
        case ConsoleRowInnerType::Content:
            RenderBoardRowContent(board, offset, inverse);
            break;
    }
}

void ConsoleChessRenderer::RenderBoardRowNonContent(int offset, bool inverse, bool isSpacer, Board * board){
    cout << "   ";

    if(!inverse){
        for(int c=0; c<8; c++)
        {
            RenderBoardRowNonContentColumn(offset, c, inverse, isSpacer, board);
        }
    }
    else{
        for(int c=7; c>=0; c--)
        {
            RenderBoardRowNonContentColumn(offset, c, inverse, isSpacer, board);
        }
    }

    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowNonContentColumn(int row, int col, bool inverse, bool isSpacer, Board * board){
    cout << "|";
    Colour squareColour = board->GetSquareColour(row, col);
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
    Colour squareColour = board->GetSquareColour(row, col);
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

pair<Move *, MovePieceResult> ConsoleChessRenderer::MakeMove(Colour colour, Board * board){
    string startPosition, endPosition;
    int startBoardPosition, endBoardPosition;
    Piece * startPiece = nullptr;
    bool opponentPiece = false;

    cout << endl;
    cout << Utility::ColourStrings[colour] << ", please enter the reference of the piece you would like to move. To offer a draw type '-', to resign type '!' .";
    cout << endl;
    cout << "Reference: " << flush;

    do{
    	opponentPiece = false;
        cin >> startPosition;

        if(startPosition.length() > 0){
        	if(startPosition[0] == '-'){
        		if(ConfirmChoice("\n\nAre you sure you want to offer a draw?")){
        			return make_pair(nullptr, MovePieceResult::OfferDraw);
        		}
        	}
        	else if(startPosition[0]=='!'){
        		if(ConfirmChoice("\n\nAre you sure you want to resign?")){
        			return make_pair(nullptr, MovePieceResult::Resign);
        		}
        	}
        }

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

void ConsoleChessRenderer::RenderMoves(vector<Move *> moves){
	int moveNumber = 0;
	cout << "\nMove history:" << endl;
	for(int m = 0; m < (int)moves.size(); m++){
		Move * move = moves[m];
		if(move->GetColour() == Colour::White){
			moveNumber++;
			cout << moveNumber << ". ";
		}
		else{
			cout << " ";
		}

		cout << move->ToString();

		if(move->GetColour() == Colour::Black && m != ((int)moves.size() - 1)){
			cout << ", ";
		}
	}

	cout << "\n";
}

Piece * ConsoleChessRenderer::PromotePiece(Colour colour, Board * board){
	cout << "\n" + string(Utility::ColourStrings[colour]) + " please select the piece type to promote to:\n\n";
	cout << "   1   Knight\n   2   Bishop\n   3   Rook\n   4   Queen\n\n";

	int pieceType = 0;
	string input;
	Piece * newPiece = nullptr;
	while(pieceType==0){
		cout << "Option: ";
		cin >> input;
		if(input.length() > 1 || input[0] < 49 || input[0] > 52){
			cout << "Invalid input, please try again.\n";
			continue;
		}
		break;
	}

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
	return newPiece;
}

bool ConsoleChessRenderer::ConfirmChoice(string message){
	cout << message << "\n   Y   Yes\n   N   No\n\nOption: ";
	string input;
	cin >> input;
	while(input != "Y" && input != "y" && input != "N" && input != "n"){
		cout << "\nIncorrect input, please try again:";
		cin >> input;
	}
	return (input == "Y" || input == "y");
}

AIType * ConsoleChessRenderer::GetAIType(vector<AIType *> aiTypes){
	cout << "\nPlease choose the AI for this player:\n";

	for(int i=0; i<(int)aiTypes.size(); i++){
		cout << "\n   " << i+1 << "   " << aiTypes.at(i)->GetName() << "\n   " << aiTypes.at(i)->GetDescription();
	}

	string input;
	AIType * type = nullptr;
	while(type == nullptr){
		cout << "\nOption: ";
		cin >> input;

		stringstream stream(input);
		int value;
		stream >> value;


		if(!stream){
			cout << "\n Incorrect entry, please try again.";
			continue;
		}

		value -= 1;
		if(value >= 0 && value < (int)aiTypes.size()){
			type = aiTypes.at(value);
		}
		else{
			cout << "\n Incorrect entry, please try again.";
		}
	}

	return type;
}

