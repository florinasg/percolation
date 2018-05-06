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



class SickTown {
public:
	virtual ~SickTown();

	SickTown(int city_dimension, double infection_probability, double mutation_probabilty, double immunization_factor );

	int INFECT_TOWN();


	int EPIDEMIC_SPREADING();



private:
	enum Health_State {sane, ill ,recovered, infection_risk};

	typedef struct human {
		human(): health_state(sane), pathogen_mutations({}),mutation_counter(0),
				recover_pathogen_mutation(-1), immune(false),Immunization_Factor(0.0) ,infection_time_step(-1){};
		Health_State health_state ;
		std::vector<int> pathogen_mutations ; /*vector keeps track of pathogen mutations ; also non_empty means chance for infection*/
		int mutation_counter; /*< MUT_MAX*/
		int recover_pathogen_mutation ; /*-1  (STADARD),stores pathogen mutation s when recovery occured */
		bool immune; /*human is either immune or not*/


		double Immunization_Factor;

		int infection_time_step;

	}human;


	/*will store the city_dimension * city_dimension town with the infected individuals*/
	human **town;

	int City_Dimension;

	int Time_Step;


	std::uniform_real_distribution<double> *distribution_prob;
	std::uniform_int_distribution<double> *distribution_mutation;
	std::default_random_engine generator;


	double Infection_Probability;



	double Mutation_Probability;

};

#endif /* SICKTOWN_H_ */
