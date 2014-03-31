#include "game.h"
#include "ChessRenderer.h"
#include "ChessUtils.h"

using namespace Chess;
using namespace Chess::Renderer;
using namespace std;

Game::Game(BaseRenderer * _renderer){
	activePlayer = Colour::White;
	status = GameStatus::Active;
	isCheck = false;
    moves = vector<string>();
    renderer = _renderer;
    board = new Board();
    whitePlayerType = blackPlayerType = PlayerType::Human;
}

void Game::Start(){
	renderer->StartGame();
	whitePlayerType = renderer->GetPlayerType(Colour::White);
	blackPlayerType = renderer->GetPlayerType(Colour::Black);

	renderer->RenderBoard(board, false);

	while(status == GameStatus::Active || status == GameStatus::InCheck){
		MovePieceResult m = renderer->MakeMove(activePlayer, board);
		switch(m)
		{
			case MovePieceResult::OK:
			case MovePieceResult::Check:
				activePlayer = activePlayer == Colour::White ? Colour::Black : Colour::White;
				renderer->RenderBoard(board, activePlayer == Colour::Black);
				if(m == MovePieceResult::Check){
					renderer->RenderMessage(string(Utility::ColourStrings[activePlayer]) + ", you are in check!");
					status = GameStatus::InCheck;
					((King *)board->GetKing(activePlayer))->SetChecked();
				}
				else{
					status = GameStatus::Active;
				}

				if(!board->TestPlayerHasMoves(activePlayer)){
					status = (status == GameStatus::InCheck ? GameStatus::Mate : GameStatus::Stalemate);
				}
				break;
			case MovePieceResult::InvalidMove:
				renderer->RenderMessage("\nInvalid move, please try again.");
				break;
			case MovePieceResult::IllegalMove:
				renderer->RenderMessage("\nIllegal move, this move would leave your King in check!");
				break;

		}
	}

	if(status == GameStatus::Mate){
		renderer->RenderMessage("\nCheckmate! " + string(Utility::ColourStrings[(activePlayer == Colour::White ? Colour::Black : Colour::White)]) + " wins.");
	}
	else{
		renderer->RenderMessage("\nStalemate! " + string(Utility::ColourStrings[activePlayer]) + " has no legal moves.");
	}

	return;
}
