#include "chess.h"
#include "piece.h"
#include "knight.h"
#include <string>
using namespace std;
using namespace Chess;

Knight::Knight(PieceColour _colour): Piece(3, _colour) {}

string Knight::GetName() { return "Knight"; }