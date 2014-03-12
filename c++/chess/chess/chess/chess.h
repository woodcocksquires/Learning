#ifndef CHESS
#define CHESS

#include <string>
#include "literals.h"

using namespace std;

namespace Chess {
	enum PieceColour: int { Black, White };
	static const char * PieceColourStrings[2] { "white", "black" };
}

#endif
