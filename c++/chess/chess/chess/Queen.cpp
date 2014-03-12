#include "chess.h"
#include "piece.h"
#include "queen.h"
#include <string>
using namespace std;
using namespace Chess;

Queen::Queen(PieceColour _colour): Piece(9, _colour) {}

string Queen::GetName() { return "Queen"; }