#include "chess.h"
#include "piece.h"
#include "ChessUtils.h"
#include <string>
using namespace std;
using namespace Chess;

Piece::Piece(int _value, Colour _colour, string _name, char _shortName):
    value(_value), colour(_colour), name(_name), shortName(_shortName) {}

int Piece::GetValue(){
	return value;
}

string Piece::GetName(){
    return name;
}

const char * Piece::GetShortName(){
    return &Utility::ColourStrings[colour][0];
}
