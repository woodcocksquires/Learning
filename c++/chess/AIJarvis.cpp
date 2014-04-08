/*
 * AIJarvis.cpp
 *
 *  Created on: 7 Apr 2014
 *      Author: Andrew.squires
 */

#include "AIJarvis.h"
#include <utility>
#include "chess.h"
#include "Board.h"
#include "move.h"
#include "stdlib.h"

using namespace std;
using namespace Chess;

namespace Chess {

	AI_Jarvis::AI_Jarvis(): AI("Jarvis"){}

	AI_Jarvis::~AI_Jarvis(){
		// TODO Auto-generated destructor stub
	}

	pair<int, int> AI_Jarvis::MakeMove(Board * board, vector<Move *> moves){
		vector<pair<int, int>> possibleMoves;
		for(int s = 0; s<SQUARE_COUNT; s++){
			Piece * piece = board->PieceAtPosition(s);
			if(piece != nullptr){
				vector<int> * pieceMoves = piece->GetPossibleMoves();
				for(int m=0; m<pieceMoves->size(); m++){
					Board copyBoard = Board(*board);
					if(copyBoard.TestLegalMove(s, pieceMoves->at(m))){
						possibleMoves.push_back(make_pair(s, pieceMoves->at(m)));
					}
				}
				delete pieceMoves;
			}
		}

		return possibleMoves.at(rand() % possibleMoves.size());
	}
} /* namespace Chess */
