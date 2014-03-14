#include "chess.h"
#include "piece.h"
#include "knight.h"
#include <string>
using namespace std;
using namespace Chess;

Knight::Knight(Colour _colour): Piece(3, _colour) {}

string Knight::GetName() { return "Knight"; }
