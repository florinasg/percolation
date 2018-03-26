/*
 * forest.h
 *
 *  Created on: 24.03.2018
 *      Author: Florian Anderl
 */

#include <time.h>
#include <stdlib.h>
#include <random>
#include <vector>

#ifndef FOREST_H_
#define FOREST_H_

enum tree_stat {green, burning, burnedDown};

typedef struct{
	double X;
	double Y;
bool tree;
tree_stat Tree_Stat;
int ignitionTime;
}root;


class Forest {
public:
	Forest(double Forest_Dimension, double Root_Distance);
	virtual ~Forest();

	int iginte_Forest();
	int grow_Forest();

	int export_Forest();


private:

	/*L*/
	double forest_dimension;
	/*has to be a divident of forest_dimesion*/
	double root_distance;
	/*defines number of rootplaces per row of length L*/
	int root_row;
	/*defines forest*/
	std::vector<root> forest;
};

#endif /* FOREST_H_ */
