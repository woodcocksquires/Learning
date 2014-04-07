/*
 * AI.cpp
 *
 *  Created on: 7 Apr 2014
 *      Author: Andrew.squires
 */

#include "AI.h"
#include <string>

using namespace std;

namespace Chess {

	AI::AI(string _name): name(_name), colour(Colour::White){}

	AI::~AI() {
		// TODO Auto-generated destructor stub
	}

	void AI::SetColour(Colour _colour){
		colour = _colour;
	}
} /* namespace Chess */
