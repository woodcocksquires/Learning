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

using namespace std;
using namespace Chess;

namespace Chess {

	AI_Jarvis::AI_Jarvis(): AI("Jarvis"){}

	AI_Jarvis::~AI_Jarvis(){
		// TODO Auto-generated destructor stub
	}

	pair<int, int> AI_Jarvis::MakeMove(Board * board, vector<Move *> moves){
			return make_pair(0 ,0);
	}
} /* namespace Chess */
