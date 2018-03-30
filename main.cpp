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


#define FOREST_L 1000

int main(int args, char * argv[])
{

	if(atoi(argv[1])==0)
	{
		for(double tree_prob = 0.01; tree_prob<=1.00; tree_prob=tree_prob+0.01)
		{

			Forest *myForest = new Forest(FOREST_L);
			myForest->grow_Forest(tree_prob);
			myForest->iginte_Forest();
			delete myForest;

		}

	}

	/*finite -> infinite*/
	else if(atoi(argv[1])== 1)
	{

		for(double tree_prob = 0.45; tree_prob<=0.65; tree_prob=tree_prob+0.01)
		{
			for(int dimension = 100; dimension <= 10000;dimension = dimension+100)
			{
				Forest *myForest = new Forest(dimension);
				myForest->grow_Forest(tree_prob);
				myForest->iginte_Forest();
				delete myForest;
			}
		}
	}

	else
		return 0;




	return 0;
}
