/*
 * forest.h
 *
 *  Created on: 24.03.2018
 *      Author: Florian Anderl
 */

#include <time.h>
#include <stdlib.h>

#ifndef FOREST_H_
#define FOREST_H_

class forest {
public:
	forest();
	virtual ~forest();

	int iginte_forest();
	int grow_forest();


private:
	bool forest_stat[][];
};

#endif /* FOREST_H_ */
