/*
 * main.cpp
 *
 *  Created on: 24.03.2018
 *      Author: Florian Anderl
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <vector>
#include "./Forest.h"
#include <iostream>


#define FOREST_L 1000
#define	TOWN_L 1000



int main(int args, char * argv[])
{

	/*Simulates Burning Forest*/
	if(argv[1] == 0)
	{

		if(atoi(argv[2])==0)
		{
			for(double tree_prob = 0.01; tree_prob<=1.00; tree_prob=tree_prob+0.01)
			{

				Forest *myForest = new Forest(FOREST_L);
				for(int monte_carlo  = 0; monte_carlo <= FOREST_L+1; monte_carlo++)
				{
					myForest->grow_Forest(tree_prob);
					myForest->iginte_Forest();

				}
				std::cout << "Probability (Monte Carlo): " << tree_prob << "-> p: " << myForest->p_fract << " Extincion_time (Monte Carlo): " << myForest->time_step <<std::endl;

				myForest->export_Forest(3);
				delete myForest;

			}

		}

		/*finite -> infinite*/
		else if(atoi(argv[2])== 1)
		{

			for(double tree_prob = 0.59; tree_prob<=0.61; tree_prob=tree_prob+0.001)
			{
				for(int dimension = 100; dimension <= 500;dimension = dimension+100)
				{
					Forest *myForest = new Forest(dimension);
					for(int monte_carlo  = 0; monte_carlo <= dimension+1; monte_carlo++)
					{
						myForest->grow_Forest(tree_prob);
						myForest->iginte_Forest();
					}
					std::cout << "DIMENSION " << dimension << "...done\n";
					myForest->export_Forest(4);
					delete myForest;
				}
			}
		}

		else
			return 0;
	}


	/*Simulates infected town*/
	else if(atoi(argv[1]) == 1)
	{




	}

	return 0;
}
