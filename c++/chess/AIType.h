/*
 * AIType.h
 *
 *  Created on: 9 Apr 2014
 *      Author: Andrew.squires
 */

#ifndef AITYPE_H_
#define AITYPE_H_

#include <string>
#include "chess.h"
#include "ai.h"

using namespace std;
using namespace Chess;

namespace Chess {

	class AIType {
	  private:
		string name;
		string description;
	  public:
		AIType(string _name, string _description);
		virtual ~AIType();
		virtual AI * CreateInstance(Colour _colour) = 0;
		string GetName();
		string GetDescription();
	};

} /* namespace Chess */

#endif /* AITYPE_H_ */
