/*
 * AIJarvis.cpp
 *
 *  Created on: 7 Apr 2014
 *      Author: Andrew.squires
 */

#include "AIJarvis.h"
#include <utility>
#include <vector>
#include "chess.h"
#include "Board.h"
#include "move.h"
#include "stdlib.h"
#include "chesspieces.h"
#include <iostream>
#include "Chessutils.h"

using namespace std;
using namespace Chess;

namespace Chess {

	AI_Jarvis::AI_Jarvis(Colour _colour): AI(_colour){}

	AI_Jarvis::~AI_Jarvis(){
		// TODO Auto-generated destructor stub
	}

	pair<Move*, MovePieceResult> AI_Jarvis::MakeMove(Board * board, vector<Move *> inputMoves){
		vector<pair<int, int>> possibleMoves;
		for(int s = 0; s<SQUARE_COUNT; s++){
			Piece * piece = board->PieceAtPosition(s);
			if(piece != nullptr && piece->GetColour() == colour){
				vector<int> * pieceMoves = piece->GetPossibleMoves();

				for(int m=0; m<(int)pieceMoves->size(); m++){
					Board copyBoard = Board(*board);
					if(copyBoard.TestLegalMove(s, pieceMoves->at(m)) == MovePieceResult::OK){
						possibleMoves.push_back(make_pair(s, pieceMoves->at(m)));
					}
				}
				delete pieceMoves;
			}
		}

		pair<int, int> randMove = possibleMoves.at(rand() % possibleMoves.size());
		pair<Move *, MovePieceResult> result = board->MovePiece(randMove.first, randMove.second);
		if(result.second == MovePieceResult::Promote){
			Piece * newPiece = board->MakePiece<Queen>(colour, 0);
			board->PromotePiece(newPiece);
			((Move *)result.first)->SetPawnPromotion(newPiece);
			result.second = MovePieceResult::OK;
		}
		return result;
	}
} /* namespace Chess */
