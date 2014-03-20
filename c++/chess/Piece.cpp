#include "chess.h"
#include "piece.h"
#include "ChessUtils.h"
#include "board.h"
#include <string>
using namespace std;
using namespace Chess;

Piece::Piece(int _value, Colour _colour, const string _name, const char _shortName, int _boardPosition, Board * _board):
    value(_value), colour(_colour), name(_name) {
    shortName = Utility::ColourStrings[colour][0];
    shortName += _shortName;
    boardPosition = _boardPosition;
    board = _board;
}

int Piece::GetValue(){
	return value;
}

string Piece::GetName(){
    return name;
}

string Piece::GetShortName(){
    return shortName;
}
