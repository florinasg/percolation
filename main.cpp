/*
 * main.cpp
 *
 *  Created on: 24.03.2018
 *      Author: Florian Anderl
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <vector>
#include "forest.h"


int main(int args, char * argv[])
{

	Forest *myForest = new Forest;


	for(double tree_prob = 0.05; tree_prob<=1; tree_prob=tree_prob+0.05)
	{
	myForest->grow_Forest(tree_prob);
	myForest->iginte_Forest();
	}


	return 0;
}
