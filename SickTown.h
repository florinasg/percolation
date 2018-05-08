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
#include <fstream>

template <typename T>
void print(T t)
{

  std::cout << t << " " << std::flush;
}

template<typename T, typename... Args>
void print(T t, Args... args)
{

  std::cout << t << " ";
  print(args...) ;
}




class SickTown {
public:
	virtual ~SickTown();

	SickTown(int city_dimension, double infection_probability, double mutation_probabilty, double immunization_factor );

	int INFECT_TOWN();


	int EPIDEMIC_SPREADING();



private:
	enum Health_State {sane, ill , recovered,  infection_risk};

	typedef struct human {
		human(): health_state(sane), pathogen_mutations({}),
				recovered_pathogen_mutation({}),infected_pathogen_mutation({}), mutation_counter(0),
				immune(false),Immunization_Factor(0.0) ,infection_time_step(-1), previous_health_state(sane){};
		Health_State health_state ;
		std::vector<int> pathogen_mutations ; /*vector keeps track of exposed pathogen mutations*/
		std::vector<int> recovered_pathogen_mutation ;
		std::vector<int> infected_pathogen_mutation ;
		int mutation_counter; /*< MUT_MAX*/
		bool immune; /*human is either immune or not*/


		double Immunization_Factor;

		int infection_time_step;

		Health_State previous_health_state; /*stores temporarily the information
		about the previous health state of the patient*/


	}human;


	/*will store the city_dimension * city_dimension town with the infected individuals*/
	human **town;

	int City_Dimension;

	int Time_Step;

	std::uniform_real_distribution<double> *distribution_prob;
	std::uniform_int_distribution<int> *distribution_mutation;
	std::default_random_engine generator;

	double Infection_Probability;
	double Mutation_Probability;

	double phi_1;
	double phi_2;

	double humans_sick_;
	double humans_recovered_;

	std::ofstream file;
	std::ofstream test;
};

#endif /* SICKTOWN_H_ */
