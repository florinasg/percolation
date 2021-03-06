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
#include <fstream>



#ifndef FOREST_H_
#define FOREST_H_

enum tree_stat {none, green, burning, burnedDown};

typedef struct{
bool tree;
tree_stat Tree_Stat;
int ignitionTime;
}root;


class Forest {
public:
	Forest(int dimension);
	virtual ~Forest();

	int iginte_Forest();
	int grow_Forest(double new_tree_prob);

	int export_Forest(int mode);



	double tree_prob;

	/*burnt trees/number of all trees*/
	double p_fract;
	double extinction_time;

	int forest_dimension;

	double number_of_trees;

	double number_of_burnt_trees;

	double p;

	int root_row;

	/*defines forest to be burnt to the ground*/
	root **forest;

	double time_step;
};

#endif /* FOREST_H_ */
