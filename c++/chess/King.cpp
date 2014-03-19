#include "chess.h"
#include "piece.h"
#include "king.h"
#include <string>
using namespace std;
using namespace Chess;

King::King(Colour _colour): Piece(0, _colour, "King", 'K') {}
