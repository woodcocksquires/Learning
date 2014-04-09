/*
 * AITypeJarvis.cpp
 *
 *  Created on: 9 Apr 2014
 *      Author: Andrew.squires
 */

#include "AIType.h"
#include "AITypeJarvis.h"
#include "AIJarvis.h"
#include "chess.h"

using namespace Chess;

namespace Chess {

	AIType_Jarvis::AIType_Jarvis() : AIType("Jarvis", "Makes random moves. Likes Bob Ross paintings!"){}

	AIType_Jarvis::~AIType_Jarvis() {
		// TODO Auto-generated destructor stub
	}

	AI * AIType_Jarvis::CreateInstance(Colour _colour){
		return new AI_Jarvis(_colour);
	}

} /* namespace Chess */


