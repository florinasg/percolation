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

#define FOREST_L 1000

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
	Forest();
	virtual ~Forest();

	int iginte_Forest();
	int grow_Forest(double new_tree_prob);

	int export_Forest(int mode);


private:

	double tree_prob;

	const int forest_dimension = FOREST_L;

	double number_of_trees;

	double number_of_unburnt_trees;

	double p;

	int root_row;
	/*defines forest*/
	root forest[FOREST_L][FOREST_L];

	int time_step;
};

#endif /* FOREST_H_ */
