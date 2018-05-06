/*
 * SickTown.h
 *
 *  Created on: 07.04.2018
 *      Author: Florian Anderl
 */

#ifndef SICKTOWN_H_
#define SICKTOWN_H_

#include <vector>
#include <utility>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include <random>


#define MUT_MAX 100

class SickTown {
public:
	SickTown();
	virtual ~SickTown();

	SickTown(int city_dimension);

	int INFECT_TOWN();


	int EPIDEMIC_SPREADING();



private:
	enum Health_State {sane, ill ,recovered};

	typedef struct human {
		human(): health_state(sane), pathogen_mutations({}),mutation_counter(0),
				recover_pathogen_mutation(-1), immune(false), infection_time_step(-1){};
		Health_State health_state ;
		std::vector<int> pathogen_mutations ; /*vector keeps track of pathogen mutations ; also non_empty means chance for infection*/
		int mutation_counter; /*< MUT_MAX*/
		int recover_pathogen_mutation ; /*-1  (STADARD),stores pathogen mutation s when recovery occured */
		bool immune; /*human is either immune or not*/

		int infection_time_step;

	}human;


	/*will store the city_dimension * city_dimension town with the infected individuals*/
	human **town;

	int City_Dimension;

	int Time_Step;

};

#endif /* SICKTOWN_H_ */
