#include "game.h"
#include "ChessRenderer.h"
#include "ChessUtils.h"
#include <utility>

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
	vector<Move *> moves = vector<Move *>();

	renderer->RenderBoard(board, false);
	Colour previousPlayer = Colour::White;

	while(status == GameStatus::Active || status == GameStatus::InCheck){
		pair<Move *, MovePieceResult> * result;
		result = renderer->MakeMove(activePlayer, board);
		MovePieceResult m = result->second;
		switch(m)
		{
			case MovePieceResult::OK:
			case MovePieceResult::Check:
			case MovePieceResult::Promote:
				previousPlayer = activePlayer;
				activePlayer = activePlayer == Colour::White ? Colour::Black : Colour::White;
				if(m == MovePieceResult::Promote){
					Piece * newPiece = renderer->PromotePiece(previousPlayer, board);
					((Move *)result->first)->SetPawnPromotion(newPiece);
					if(board->TestCheck(activePlayer)){
						m = MovePieceResult::Check;
						status = GameStatus::InCheck;
						result->second = m;
					}
					if(!board->TestPlayerHasMoves(activePlayer)){
						renderer->RenderBoard(board, previousPlayer == Colour::Black);
						break;
					}
				}
				renderer->RenderBoard(board, activePlayer == Colour::Black);
				if(m == MovePieceResult::Check){
					renderer->RenderMessage(string(Utility::ColourStrings[activePlayer]) + ", you are in check!");
					status = GameStatus::InCheck;
					((King *)board->GetKing(activePlayer))->SetChecked(true);
				}
				else{
					status = GameStatus::Active;
					((King *)board->GetKing(previousPlayer))->SetChecked(false);
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
		moves.push_back(result->first);
		delete result;
	}

	for(int m = 0; m < moves.size(); m++){
		delete moves.at(m);
	}

	if(status == GameStatus::Mate){
		renderer->RenderMessage("\nCheckmate! " + string(Utility::ColourStrings[(activePlayer == Colour::White ? Colour::Black : Colour::White)]) + " wins.");
	}
	else{
		renderer->RenderMessage("\nStalemate! " + string(Utility::ColourStrings[activePlayer]) + " has no legal moves.");
	}

	return;
}
