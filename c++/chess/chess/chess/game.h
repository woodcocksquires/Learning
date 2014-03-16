#ifndef GAME_H
#define GAME_H

#include "ChessRenderer.h"
#include "Chess.h"
#include "Move.h"
#include <vector>

using namespace std;
using namespace Chess;
using namespace Chess::Renderer;

namespace Chess {
    class Game
    {
        PlayerType whitePlayerType, blackPlayerType;
        BaseRenderer * renderer;
        Board * board;
        Colour activePlayer = Colour::White;
        bool isCheck = false;
        GameStatus status = GameStatus::Active;
        vector<Move> * moves;
      public:
        Game(BaseRenderer * _renderer);
    };
}
#endif // GAME_H
