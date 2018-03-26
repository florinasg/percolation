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
	double forest_dimension = atof(argv[1]);
	double root_distance = atof(argv[2]);
	Forest *myForest = new Forest(forest_dimension, root_distance);


	myForest->grow_Forest();

	myForest->iginte_Forest();


	return 0;
}
