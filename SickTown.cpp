/*
 * SickTown.cpp
 *
 *  Created on: 07.04.2018
 *      Author: Florian Anderl
 */

#include "SickTown.h"
#include <algorithm>

SickTown::SickTown() {
	// TODO Auto-generated constructor stub

}

SickTown::~SickTown() {
	// TODO Auto-generated destructor stub
}


SickTown::SickTown(int city_dimension)
{

	City_Dimension = city_dimension;

	Time_Step = 0;

	/*Defines Town with standar initialization
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


	/*Infection:
	 * -> periodic boundary conditions*/
	for(int i = 0; i < City_Dimension; i++)
	{
		/*Default Allocation*/
		idx = i;

		if(i == 0)
		{

		}

		/*Boundary Condition*/
		else if(i == City_Dimension-1)
		{

		}


		for(int j = 0; j < City_Dimension; j++)
		{

			/*Default Allocation*/
			jdx = j;

			/*Boundary Condition*/
			if(j == 0)
			{

			}

			/*Boundary Condition*/
			else if(j == City_Dimension-1)
			{

			}

			if(town[idx][jdx].health_state == ill)
			{


				/*RIGHT NEIGHBOUR*/
				town[idx][jdx+1].pathogen_mutations.
				push_back(town[idx][jdx].pathogen_mutations.back());

				/*LEFT NEIGHBOUR*/
				town[idx][jdx-1].pathogen_mutations.
				push_back(town[idx][jdx].pathogen_mutations.back());


				/*UPPER NEIGHBOUR*/
				town[idx-1][jdx].pathogen_mutations.
				push_back(town[idx][jdx].pathogen_mutations.back());

				/*BOTTOM NEIGHBOUR*/
				town[idx+1][jdx].pathogen_mutations.
				push_back(town[idx][jdx].pathogen_mutations.back());


			}


		}
	}






	return 0;
}
