#ifndef GAME_H
#define GAME_H

#include "ChessRenderer.h"
#include "Chess.h"
#include <vector>
#include "ai.h"

using namespace std;
using namespace Chess;
using namespace Chess::Renderer;

namespace Chess {
    class Game
    {
        PlayerType whitePlayerType, blackPlayerType;
        BaseRenderer * renderer;
        Board * board;
        Colour activePlayer;
        bool isCheck;
        GameStatus status;
        vector<string> moves;
        vector<AI *> aiPlayers;
      public:
        Game(BaseRenderer * _renderer);
        ~Game();
        void Start();
        void AddAIPlayer(AI *);
    };
}
#endif // GAME_H
