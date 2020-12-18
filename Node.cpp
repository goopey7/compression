//
// Created by Sam Collier on 24/11/2020.
//

#include <iostream>
#include "Node.h"

// this is just for debugging. TODO: print tree diagram function
std::string Node::toString()
{
	int rightKey=-1;
	int leftKey = -1;
	if(right!= nullptr)rightKey=right->getKey();
	if(left!= nullptr)leftKey=left->getKey();
	std::string rightStr = "RIGHT KEY: "+std::to_string(rightKey);
	std::string leftStr = "LEFT KEY: "+std::to_string(leftKey);
	return "KEY: "+std::to_string(key)+"\n"+leftStr+'\n'+rightStr;
}
