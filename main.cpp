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
#include "SickTown.h"
#include <iostream>



/*Important Constants for use in Simulation*/
#define FOREST_L 200 /*Forest Dimension*/
#define	TOWN_L 1000 /*Town Dimension*/



int main(int args, char * argv[])
{

	/*Simulates Burning Forest for different tree densities*/
	if(atoi(argv[1]) == 0)
	{

		if(atoi(argv[2])==0)
		{
			/*calculates */
			for(double tree_prob = 0.01; tree_prob<=1.00; tree_prob=tree_prob+0.01)
			{

				Forest *myForest = new Forest(FOREST_L);
				/*Monte Carlo Step*/
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

		/*finite -> infinite (does not really work but implementation should be correct)
		 * checks where the burnt tree density scales like forest dimension*/
		else if(atoi(argv[2])== 1)
		{

			for(double tree_prob = 0.59; tree_prob<=0.61; tree_prob=tree_prob+0.001)
			{
				/*Calculation for tree dimensions 100-500 -> RUNTIME*/
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


	/*Simulates Infected Town*/
	else if(atoi(argv[1]) == 1)
	{
		SickTown *myTown;
		print("Infected Town Simulation started...\n");

		for(double inf = 0.1; inf <=1; inf = inf +0.1)
		{

			for(double imm = 0; imm <=1; imm=imm+0.5)
			{
				/*args=[Town Dimension, infection probability, mutation probability
				 * immunity factor]*/
				myTown = new SickTown(TOWN_L,inf,0,imm);
				myTown->INFECT_TOWN();

				/*MONTE CARLO STEPS*/
				for(int i = 0; i < 100000; i++)

				{
					myTown->EPIDEMIC_SPREADING();

				}
			}

			delete myTown;
		}
	}


	else {return 0;}

	return 0;
}
