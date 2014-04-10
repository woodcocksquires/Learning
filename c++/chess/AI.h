/*
 * AI.h
 *
 *  Created on: 7 Apr 2014
 *      Author: Andrew.squires
 */

#ifndef AI_H_
#define AI_H_

#include <string>
#include <utility>
#include "chess.h"
#include "board.h"

using namespace std;
using namespace Chess;

namespace Chess {

class AI {
  protected:
	Colour colour;
  public:
	virtual ~AI();
	AI(Colour _colour);
	virtual pair<Move *, MovePieceResult> MakeMove(Board * board, vector<Move *> moves) = 0;
};

} /* namespace Chess */

#endif /* AI_H_ */
