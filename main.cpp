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


int main()
{
	forest *myForest = new forest();


	myForest->grow_forest();

	myForest->iginte_forest();


	return 0;
}
