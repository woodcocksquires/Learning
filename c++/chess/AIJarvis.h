/*
 * AIJarvis.h
 *
 *  Created on: 7 Apr 2014
 *      Author: Andrew.squires
 */

#ifndef AIJARVIS_H_
#define AIJARVIS_H_

#include <utility>
#include "chess.h"
#include "move.h"
#include "board.h"
#include "ai.h"

using namespace std;
using namespace Chess;

namespace Chess {

	class AI_Jarvis: public AI {
	  public:
		AI_Jarvis(Colour _colour);
		virtual ~AI_Jarvis();
		virtual pair<Move *, MovePieceResult> MakeMove(Board * board, vector<Move *> moves);
		virtual bool EvaluateDrawOffer();
	};

} /* namespace Chess */

#endif /* AIJARVIS_H_ */
