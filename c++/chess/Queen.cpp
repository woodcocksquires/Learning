#include "chess.h"
#include "piece.h"
#include "queen.h"
#include <string>
using namespace std;
using namespace Chess;

Queen::Queen(Colour _colour): Piece(9, _colour, "Queen", 'Q') {}
