#include "chess.h"
#include "piece.h"
#include "rook.h"
#include <string>
using namespace std;
using namespace Chess;

Rook::Rook(Colour _colour): Piece(5, _colour, "Rook", 'R') {}
