#include "chess.h"
#include "piece.h"
#include <string>
using namespace std;
using namespace Chess;

Piece::Piece(int _value, Colour _colour): value(_value), colour(_colour) {}

int Piece::GetValue(){
	return value;
}
