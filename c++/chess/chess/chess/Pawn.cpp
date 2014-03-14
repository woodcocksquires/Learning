#include "chess.h"
#include "piece.h"
#include "pawn.h"
#include <string>
using namespace std;
using namespace Chess;

Pawn::Pawn(Colour _colour): Piece(1, _colour) {}

string Pawn::GetName() { return "Pawn"; }
