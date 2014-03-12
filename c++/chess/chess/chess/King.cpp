#include "chess.h"
#include "piece.h"
#include "king.h"
#include <string>
using namespace std;
using namespace Chess;

King::King(PieceColour _colour): Piece(0, _colour) {}

string King::GetName() { return "King"; }