#include "chess.h"
#include "piece.h"
#include "bishop.h"
#include <string>

using namespace std;
using namespace Chess;

Bishop::Bishop(PieceColour _colour): Piece(0, _colour) {}

string Bishop::GetName() { return "Bishop"; }