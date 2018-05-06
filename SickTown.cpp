/*
 * SickTown.cpp
 *
 *  Created on: 07.04.2018
 *      Author: Florian Anderl
 */

#include "SickTown.h"
#include <algorithm>
#include <time.h>



SickTown::~SickTown() {
	// TODO Auto-generated destructor stub
}


SickTown::SickTown(int city_dimension, double infection_probability, double mutation_probabilty, double immunization_factor)
{

	City_Dimension = city_dimension;

	Infection_Probability = infection_probability;

	Mutation_Probability = mutation_probabilty;


	distribution_prob = new std::uniform_real_distribution<double> (0,1);
	distribution_mutation = new std::uniform_int_distribution<int> (1,100);

	generator.seed(time(NULL));





	Time_Step = 0;

	/*Defines Town with standard initialization
	 * for each individual*/
	town = new human*[city_dimension];
	for(int i = 0; i < city_dimension; ++i) {
		town[i] = new human[city_dimension];
	}

	for(int idx = 0; idx < city_dimension; idx ++)
	{
		for(int jdx = 0; jdx < city_dimension; jdx ++)
		{
			town[idx][jdx] = human();
			town[idx][jdx].Immunization_Factor = immunization_factor;
		}
	}



}

int SickTown::INFECT_TOWN()
{
	std::vector<int> arr_rand_infect_idx;
	int rand_infect_idx = -1;


	/*TODO: TEST & VERIFY 12:24 ETC+1*/
	for(int idx = 0; idx < ((City_Dimension*City_Dimension)/100); idx ++)
	{
		/*generates random lattice index*/
		rand_infect_idx = rand() % (City_Dimension*City_Dimension);


		if(std::find(arr_rand_infect_idx.begin(), arr_rand_infect_idx.end(), rand_infect_idx) != arr_rand_infect_idx.end())
		{
			idx = idx -1;
		}
		else
		{
			/*translates index from 1D to 2D*/
			int idx = rand_infect_idx/City_Dimension;
			int jdx = rand_infect_idx % City_Dimension;

			town[idx][jdx].health_state = ill;
			town[idx][jdx].infection_time_step = 0;
			town[idx][jdx].pathogen_mutations.push_back(int(0));
			/*pushes lattice index into vector
			 * in order to not use it twice*/
			arr_rand_infect_idx.push_back(int(rand_infect_idx));
		}
	}


	return 0;
}


int SickTown::EPIDEMIC_SPREADING()
{

	int idx = -1;
	int jdx = -1;
	int jdx_left = -1;
	int jdx_right = -1;
	int idx_up = -1;
	int idx_bottom = -1;


	/*Infection:
	 * -> periodic boundary conditions*/
	for(int i = 0; i < City_Dimension; i++)
	{
		/*Default Allocation*/
		idx = i;
		idx_bottom = i+1;
		idx_up = i-1;

		if(i == 0)
		{
			idx_up = City_Dimension - 1;
		}

		/*Boundary Condition*/
		else if(i == City_Dimension-1)
		{
			idx_bottom = 0;
		}


		for(int j = 0; j < City_Dimension; j++)
		{

			/*Default Allocation*/
			jdx = j;

			/*Boundary Condition*/
			if(j == 0)
			{
				jdx_left = City_Dimension -1;
			}

			/*Boundary Condition*/
			else if(j == City_Dimension-1)
			{
				jdx_right = 0;
			}

			if(town[idx][jdx].health_state == ill)
			{


				/*RIGHT NEIGHBOUR*/
				town[idx][jdx_right].pathogen_mutations.
				push_back(town[idx][jdx].pathogen_mutations.back());
				town[idx][jdx_right].health_state = infection_risk;

				/*LEFT NEIGHBOUR*/
				town[idx][jdx_left].pathogen_mutations.
				push_back(town[idx][jdx].pathogen_mutations.back());
				town[idx][jdx_left].health_state = infection_risk;


				/*UPPER NEIGHBOUR*/
				town[idx_up][jdx].pathogen_mutations.
				push_back(town[idx][jdx].pathogen_mutations.back());
				town[idx_up][jdx].health_state = infection_risk;


				/*BOTTOM NEIGHBOUR*/
				town[idx_bottom][jdx].pathogen_mutations.
				push_back(town[idx][jdx].pathogen_mutations.back());
				town[idx_bottom][jdx].health_state = infection_risk;


			}


		}
	}



	/*FUN TIME
	 * */
	for(int idx = 0; idx < City_Dimension; idx ++)
	{
		for(int jdx = 0; jdx < City_Dimension; jdx ++)
		{

			if(town[idx][jdx].health_state==infection_risk)
			{

				/*If human is not infected with pathogen_mutation
				 *
				 *
				 * TODO: VERIFY, might very likely fail !!!*/
				if(std::find(town[idx][jdx].pathogen_mutations.begin(),
						town[idx][jdx].pathogen_mutations.end()-1,
						town[idx][jdx].pathogen_mutations.back()) !=
								town[idx][jdx].pathogen_mutations.end())
				{
					if(distribution_prob(generator) <= Infection_Probability)
					{

						/*MUTATION*/





						town[idx][jdx].health_state = ill;
						town[idx][jdx].infection_time_step = Time_Step;

					}

				}


				/* Human was previously infected with pathogen_mutation
				 * */
				else
				{
					if(distribution_prob(generator) <=
							(Infection_Probability*town[idx][jdx].Immunization_Factor))
					{


						/*MUTATION*/

						town[idx][jdx].health_state = ill;
						town[idx][jdx].infection_time_step = Time_Step;

					}


				}


			}



		}
	}


	/*Increments Monte-Carlo-Step*/
	Time_Step++;


	return 0;
}
