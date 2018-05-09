/*
 * SickTown.cpp
 *
 *  Created on: 07.04.2018
 *      Author: Florian Anderl
 */

#include "SickTown.h"
#include <algorithm>
#include <time.h>


#define MUT_MAX 1000

SickTown::~SickTown() {
	// TODO Auto-generated destructor stub
	file.close();

}


SickTown::SickTown(int city_dimension, double infection_probability, double mutation_probabilty, double immunization_factor)
{

	file.open("SICK_TOWN_(p="+std::to_string(infection_probability)+",q="+std::to_string(
			immunization_factor)+",lambda="+std::to_string(mutation_probabilty)+").csv");


	/*Table Information*/
	file << "time step,phi_1,phi_2\n";

	City_Dimension = city_dimension;

	Infection_Probability = infection_probability;

	Mutation_Probability = mutation_probabilty;



	distribution_prob = new std::uniform_real_distribution<double> (0,1);
	distribution_mutation = new std::uniform_int_distribution<int> (1,100);

	generator.seed(time(NULL));


	/*Default Initializations*/
	phi_1=0;
	phi_2=0;
	Time_Step = 1;

	/*Defines Town with standard initialization
	 * for each individual*/
	town = new human*[city_dimension];
	for(int i = 0; i < city_dimension; i ++) {
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


	srand (time(NULL));





	for(int i = 0; i< ((City_Dimension*City_Dimension)/100); i ++)
	{
		/*generates random lattice index*/
		rand_infect_idx = rand() % (City_Dimension*City_Dimension);


		if(std::find(arr_rand_infect_idx.begin(), arr_rand_infect_idx.end(), rand_infect_idx) != arr_rand_infect_idx.end())
		{
			i = i -1;
		}
		else
		{
			/*translates index from 1D to 2D -> TODO: FIX, but not so urgently*/
			int idx = rand_infect_idx/City_Dimension;
			int jdx = (rand_infect_idx % City_Dimension);

			town[idx][jdx].health_state = ill;
			town[idx][jdx].infection_time_step = 0;
			town[idx][jdx].pathogen_mutations.push_back(int(0));
			town[idx][jdx].infected_pathogen_mutation.push_back(int(0));

			/*pushes lattice index into vector
			 * in order to not use it twice for new-infection*/
			arr_rand_infect_idx.push_back(int(rand_infect_idx));


			phi_1++;
			phi_2++;
			humans_sick_ ++;



		}


	}


	return 0;
}


int SickTown::EPIDEMIC_SPREADING()
{


	humans_recovered_ = 0;

	int idx = -1;
	int jdx = -1;
	int jdx_left = -1;
	int jdx_right = -1;
	int idx_up = -1;
	int idx_bottom = -1;

	bool container_check = false;


	/*this loop stores the healthstes of the humans
	 * -> in case of getting in the risk of an infection AND not being
	 * infected in the end, the previous helth state is restored
	 * -> avoids double caounting ill people*/
	for(int i = 0; i< City_Dimension; i++)
	{
		for(int j = 0; j < City_Dimension; j++)
		{
			town[i][j].previous_health_state = town[i][j].health_state;
		}
	}

	/*Infection:
	 * -> periodic boundary conditions*/
	for(int i = 0; i < City_Dimension; i++)
	{
		/*Default Allocation of help indices*/
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

			/*Default Allocation of help indices*/
			jdx = j;
			jdx_right = j+1;
			jdx_left = j-1;

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


	/* INFECTION OR NOT */

	for(int idx = 0; idx < City_Dimension; idx ++)
	{
		for(int jdx = 0; jdx < City_Dimension; jdx ++)
		{

			/*Random doubles are generate in order to compare them
			 * with defined magnitudes which leads to certain
			 * actions*/
			double prob = (*distribution_prob)(generator);
			int mutation_prob = (*distribution_mutation)(generator); /*Denotes a random number which
			represents a random mutation*/


			if(town[idx][jdx].health_state==infection_risk)
			{


				/*Checks whether newly exposed-to mutation has already been
				 * overcome before by the patient */
				if(std::find(town[idx][jdx].recovered_pathogen_mutation.begin(),
						town[idx][jdx].recovered_pathogen_mutation.end(),
						town[idx][jdx].pathogen_mutations.back()) == /* NB! Equality Required*/
								town[idx][jdx].recovered_pathogen_mutation.end())
				{
					container_check = true;
				}


				/*If human was not INFECTED with pathogen_mutation previously
				 * -> .recovered_pathogen_mutation vector does not contain recently aquired pathogen*/
				if(container_check)
				{
					if(prob <= Infection_Probability)
					{

						/*Random number for likelihood that pathogen mutates*/
						prob = (*distribution_prob)(generator);

						/*Possible MUTATION*/
						if(prob <= Mutation_Probability )
						{

							if(town[idx][jdx].pathogen_mutations.size() >= double(MUT_MAX))
							{
								town[idx][jdx].pathogen_mutations.clear();
								town[idx][jdx].pathogen_mutations.push_back(int(0))

							}
							else
							{
								if(std::find(town[idx][jdx].pathogen_mutations.begin(),town[idx][jdx].pathogen_mutations.end(),
										mutation_prob) == town[idx][jdx].pathogen_mutations.end())
								{

									town[idx][jdx].pathogen_mutations.push_back(int(mutation_prob));

								}
							}
						}


						town[idx][jdx].health_state = ill;


						town[idx][jdx].infected_pathogen_mutation.push_back(int(town[idx][jdx].
								pathogen_mutations.back()));
						town[idx][jdx].infection_time_step = Time_Step;
						if(town[idx][jdx].previous_health_state != SickTown::ill)
						{
							phi_1 ++;
							humans_sick_++;
							phi_2++;
						}
					}


					else
					{
						town[idx][jdx].health_state = town[idx][jdx].previous_health_state;
					}

				}


				/* Human was previously infected with pathogen_mutation
				 * ->  recovery vector contains gene*/
				else if(container_check == false)
				{
					if(prob <=
							(Infection_Probability*town[idx][jdx].Immunization_Factor))
					{


						/*Possible MUTATION is determined here*/
						prob = (*distribution_prob)(generator);
						if(prob<= Mutation_Probability )
						{
							/*Pathogen Mutates Back when MUT_MAX is reached*/
							if(town[idx][jdx].pathogen_mutations.size() >= double(MUT_MAX))
							{
								town[idx][jdx].pathogen_mutations.clear();
								town[idx][jdx].pathogen_mutations.push_back(int(0))

							}

							else
							{
								/*pushes the new mutation into the mutations-vector*/
								town[idx][jdx].pathogen_mutations.push_back(int(
										mutation_prob));
							}
						}


						town[idx][jdx].health_state = ill;
						town[idx][jdx].infected_pathogen_mutation.push_back(int(town[idx][jdx].
								pathogen_mutations.back()));
						town[idx][jdx].infection_time_step = Time_Step;

						/*Increases counters ONLY if human was not already sick before
						 * -> COUNTS ONLY humans that were sane before*/
						if(town[idx][jdx].previous_health_state != SickTown::ill)
						{
							phi_1 ++;
							humans_sick_++;
							phi_2++;
						}

					}

					else
					{
						town[idx][jdx].health_state = town[idx][jdx].previous_health_state;
					}



				}
			}



		}
	}



	/*Test Output*/
	//print("humans_sick_this_time_step_before_recovery: ",humans_sick_,"\n");




	/*RECOVERING PATIENTS*/
	for(int idx = 0; idx < City_Dimension; idx++)
	{
		for(int jdx = 0; jdx < City_Dimension; jdx++)

		{
			test << town[idx][jdx].health_state <<   ",";

			/*Recover if ILL due to an infection during the LAST time-step*/
			if((town[idx][jdx].health_state == ill) && (town[idx][jdx].infection_time_step == Time_Step-1))
			{
				town[idx][jdx].health_state = recovered;

				int bubu = int(town[idx][jdx].infected_pathogen_mutation.back());
				town[idx][jdx].recovered_pathogen_mutation.push_back(int(bubu));
				phi_1--;
				humans_sick_--;

				humans_recovered_ ++;
			}


		}

		test<< "\n";
	}


	/*Test Output*/
	//print("humans_recovered_this_time_step: ",humans_recovered_,"\n");

	/*Averaged Magnitudes*/
	double phi_1_print = phi_1 / (City_Dimension*City_Dimension);

	double phi_2_print = phi_2 / (City_Dimension*City_Dimension);


	/*File Output*/
	file << Time_Step << "," << phi_1_print << "," << phi_2_print << "\n";

	/*Increments Formal Monte-Carlo-Step*/
	Time_Step++;


	return 0;
}
