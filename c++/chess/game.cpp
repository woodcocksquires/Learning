#include "game.h"
#include "ChessRenderer.h"

using namespace Chess;
using namespace Chess::Renderer;
using namespace std;

Game::Game(BaseRenderer * _renderer){
	activePlayer = Colour::White;
	status = GameStatus::Active;
	isCheck = false;

    moves = vector<string>();
    renderer = _renderer;
    renderer->StartGame();
    board = new Board();
    whitePlayerType = renderer->GetPlayerType(Colour::White);
    blackPlayerType = renderer->GetPlayerType(Colour::Black);

    while(status == GameStatus::Active){
        MovePieceResult m = renderer->MakeMove(activePlayer, board);
        switch(m)
        {
        	case MovePieceResult::OK:
        		activePlayer = activePlayer == Colour::White ? Colour::Black : Colour::White;
        		renderer->RenderBoard(board, activePlayer == Colour::Black);
        		break;
        }
        status = GameStatus::Mate;
    }
}
