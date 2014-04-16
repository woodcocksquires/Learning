#ifndef GAME_H
#define GAME_H

#include "ChessRenderer.h"
#include "Chess.h"
#include <vector>
#include "ai.h"
#include "aitype.h"
#include "lua.hpp"

using namespace std;
using namespace Chess;
using namespace Chess::Renderer;

namespace Chess {
    class Game
    {
        PlayerType whitePlayerType, blackPlayerType;
        AI * whiteAI, * blackAI;
        BaseRenderer * renderer;
        Board * board;
        Colour activePlayer;
        bool isCheck;
        GameStatus status;
        vector<string> moves;
        vector<AIType *> aiPlayers;
        lua_State * luaState;
        void ProcessContinue(Colour previousPlayer, pair<Move *, MovePieceResult> result, MovePieceResult moveResult);
        void CloseLuaState();
      public:
        Game(BaseRenderer * _renderer);
        ~Game();
        void Start();
        void AddAIPlayer(AIType *);
        void AddAI();
    };
}
#endif // GAME_H
