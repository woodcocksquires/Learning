/*
 * AIType.cpp
 *
 *  Created on: 9 Apr 2014
 *      Author: Andrew.squires
 */

#include "AIType.h"
#include <string>

namespace Chess {

AIType::AIType(string _name, string _description){
	name = _name;
	description = _description;
}

AIType::~AIType() {
	// TODO Auto-generated destructor stub
}

} /* namespace Chess */

string AIType::GetName(){
	return name;
}

string AIType::GetDescription(){
	return description;
}
