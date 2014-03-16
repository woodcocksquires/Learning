#include "game.h"
#include "ChessRenderer.h"
#include "Move.h"

using namespace Chess;
using namespace Chess::Renderer;
using namespace std;

Game::Game(BaseRenderer * _renderer){
    moves = new vector<Move>();
    renderer = _renderer;
    renderer->StartGame();
    board = new Board();
    PlayerType whitePlayerType = renderer->GetPlayerType(Colour::White);
    PlayerType blackPlayerType = renderer->GetPlayerType(Colour::Black);

    while(status == GameStatus::Active){
        Move * m = renderer->RequestMove(activePlayer, board);
        status = GameStatus::Mate;
        delete m;
    }
}

