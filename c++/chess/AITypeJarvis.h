/*
 * AITypeJarvis.h
 *
 *  Created on: 9 Apr 2014
 *      Author: Andrew.squires
 */

#ifndef AITYPEJARVIS_H_
#define AITYPEJARVIS_H_

#include "AIType.h"
#include "chess.h"

using namespace Chess;

namespace Chess {

	class AIType_Jarvis: public AIType {
	  public:
		AIType_Jarvis();
		virtual ~AIType_Jarvis();
		virtual AI * CreateInstance(Colour _colour);
	};

} /* namespace Chess */

#endif /* AITYPEJARVIS_H_ */
