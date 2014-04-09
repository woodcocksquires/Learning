#ifndef GAME_H
#define GAME_H

#include "ChessRenderer.h"
#include "Chess.h"
#include <vector>
#include "ai.h"
#include "aitype.h"

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
        void ProcessContinue(Colour previousPlayer, pair<Move *, MovePieceResult> result, MovePieceResult moveResult);
      public:
        Game(BaseRenderer * _renderer);
        ~Game();
        void Start();
        void AddAIPlayer(AIType *);
    };
}
#endif // GAME_H
