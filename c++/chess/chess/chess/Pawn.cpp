#include "chess.h"
#include "piece.h"
#include "pawn.h"
#include <string>
using namespace std;
using namespace Chess;

Pawn::Pawn(PieceColour _colour): Piece(1, _colour) {}

string Pawn::GetName() { return "Pawn"; }