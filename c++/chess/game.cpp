#include "game.h"
#include "ChessRenderer.h"
#include "ChessUtils.h"
#include <utility>
#include "ai.h"
#include "aitype.h"

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
    whiteAI = blackAI = nullptr;
    aiPlayers = vector<AIType *>();
}

Game::~Game(){
	for(int a=0; a<(int)aiPlayers.size(); a++){
		delete aiPlayers.at(a);
	}
}

void Game::Start(){
	renderer->StartGame();
	whitePlayerType = renderer->GetPlayerType(Colour::White);
	blackPlayerType = renderer->GetPlayerType(Colour::Black);

	if(whitePlayerType == PlayerType::CPU){
		whiteAI = aiPlayers.at(0)->CreateInstance(Colour::White);
	}

	if(blackPlayerType == PlayerType::CPU){
		blackAI = aiPlayers.at(0)->CreateInstance(Colour::Black);
	}

	vector<Move *> moves = vector<Move *>();

	renderer->RenderBoard(board, false);
	Colour previousPlayer = Colour::White;
	bool validMove = true;
	while(status == GameStatus::Active || status == GameStatus::InCheck){
		pair<Move *, MovePieceResult> result;
		Colour opponent;
		PlayerType opponentPlayerType;

		if(moves.size() > 0 && validMove){
			renderer->RenderMoves(moves);
		}

		PlayerType currentPlayerType = (activePlayer == Colour::White ? whitePlayerType: blackPlayerType);
		AI * aiInstance;
		if(currentPlayerType == PlayerType::CPU){
			aiInstance = (activePlayer == Colour::White ? whiteAI : blackAI);
			result = aiInstance->MakeMove(board, moves);
		}
		else{
			result = renderer->MakeMove(activePlayer, board);
		}

		MovePieceResult m = result.second;
		switch(m)
		{
			case MovePieceResult::OK:
			case MovePieceResult::Check:
			case MovePieceResult::Promote:
				ProcessContinue(previousPlayer, result, m);
				validMove = true;
				break;
			case MovePieceResult::OfferDraw:
				opponent = (activePlayer == Colour::White ? Colour::Black : Colour::White);
				opponentPlayerType = (opponent == Colour::White ? whitePlayerType : blackPlayerType);
				if(opponentPlayerType == PlayerType::CPU){
					AI * opponentInstance = (opponent == Colour::White ? whiteAI : blackAI);
					if(opponentInstance->EvaluateDrawOffer()){
						status = GameStatus::Draw;
						break;
					}
					else{
						renderer->RenderMessage("\nOffer of draw declined.");
						break;
					}
				}
				else{
					if(renderer->ConfirmChoice(string(Utility::ColourStrings[opponent]) + ", would you like to accept " + string(Utility::ColourStrings[activePlayer]) + "'s offer of a draw?")){
						status = GameStatus::Draw;
						break;
					}
					else{
						renderer->RenderMessage("\nOffer of draw declined.");
						break;
					}
				}
				break;
			case MovePieceResult::Resign:
				status = GameStatus::Resigned;
				break;
			case MovePieceResult::InvalidMove:
				renderer->RenderMessage("\nInvalid move, please try again.");
				validMove = false;
				break;
			case MovePieceResult::IllegalMove:
				renderer->RenderMessage("\nIllegal move, this move would leave your King in check!");
				validMove = false;
				break;
			case MovePieceResult::RepeatDraw:
				status = GameStatus::DrawRepeated;
				break;
			case MovePieceResult::MoveDraw:
				status = GameStatus::DrawNoTaken;
				break;
			case MovePieceResult::MaterialDraw:
				status = GameStatus::DrawMaterial;
				break;
		}

		if(result.first != nullptr){
			moves.push_back(result.first);
		}
	}

	if(moves.size() > 0 && validMove){
		renderer->RenderMoves(moves);
	}

	for(int m = 0; m < (int)moves.size(); m++){
		delete moves.at(m);
	}

	renderer->RenderBoard(board, false);
	switch(status){
		case GameStatus::Mate:
			renderer->RenderMessage("\nCheckmate! " + string(Utility::ColourStrings[(activePlayer == Colour::White ? Colour::Black : Colour::White)]) + " wins.");
			break;
		case GameStatus::Stalemate:
			renderer->RenderMessage("\nStalemate! " + string(Utility::ColourStrings[activePlayer]) + " has no legal moves.");
			break;
		case GameStatus::Draw:
			renderer->RenderMessage("\nThe players agree to draw the game.");
			break;
		case GameStatus::Resigned:
			renderer->RenderMessage("\n" + string(Utility::ColourStrings[activePlayer]) + " resigns the game!");
			break;
		case GameStatus::DrawRepeated:
			renderer->RenderMessage("\nDraw! The same board position was repeated three times.");
			break;
		case GameStatus::DrawNoTaken:
			renderer->RenderMessage("\nDraw! No piece has been taken in 50 turns and no pawn has been moved.");
			break;
		case GameStatus::DrawMaterial:
			renderer->RenderMessage("\nMaterial Draw! No player is able to force checkmate.");
			break;
		default:
			break;
	}

	return;
}

void Game::AddAIPlayer(AIType * player){
	aiPlayers.push_back(player);
}

void Game::ProcessContinue(Colour previousPlayer, pair<Move *, MovePieceResult> result, MovePieceResult moveResult){
	previousPlayer = activePlayer;
	activePlayer = activePlayer == Colour::White ? Colour::Black : Colour::White;
	if(moveResult == MovePieceResult::Promote){
		Piece * newPiece = renderer->PromotePiece(previousPlayer, board);
		((Move *)result.first)->SetPawnPromotion(newPiece);
		if(board->TestCheck(activePlayer)){
			moveResult = MovePieceResult::Check;
			status = GameStatus::InCheck;
			result.second = moveResult;
		}
		if(!board->TestPlayerHasMoves(activePlayer)){
			status = (status == GameStatus::InCheck ? GameStatus::Mate : GameStatus::Stalemate);
			renderer->RenderBoard(board, previousPlayer == Colour::Black);
			return;
		}
	}
	renderer->RenderBoard(board, activePlayer == Colour::Black);
	if(moveResult == MovePieceResult::Check){
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
}
