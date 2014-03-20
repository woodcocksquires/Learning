#ifndef CHESS
#define CHESS

#include <string>
#include "literals.h"

using namespace std;

namespace Chess {
	enum Colour: int { White, Black };
	enum PlayerType: int { Human, CPU };
	enum GameStatus: int { Active, Mate, Stalemate };
	enum MovePieceResult: int { OK };
}

#endif
