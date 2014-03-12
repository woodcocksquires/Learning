#include "chess.h"
#include "piece.h"
#include "rook.h"
#include <string>
using namespace std;
using namespace Chess;

Rook::Rook(PieceColour _colour): Piece(5, _colour) {}

string Rook::GetName() { return "Rook"; }