/*
 * Forest.cpp
 *
 *  Created on: 24.03.2018
 *      Author: Florian Anderl
 */

#include "Forest.h"

Forest::Forest(double Forest_Dimension, double Root_Distance): forest_dimension(Forest_Dimension), root_distance(Root_Distance), root_row(0)
{
const int Root_row = forest_dimension/root_distance +1;
forest = new root[Root_row][Root_row];

}

Forest::~Forest() {

}

int Forest::grow_Forest()
{
	return 0;
}


int Forest::iginte_Forest()
{
	return 0;
}

int Forest::export_Forest()
{


	return 0;
}
