/*
 * Forest.cpp
 *
 *  Created on: 24.03.2018
 *      Author: Florian Anderl
 */

#include "Forest.h"
#include <utility>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <cstdlib>



/*default constructor*/
Forest::Forest() :  root_row(0), time_step(0)
{

	time_step = 1;

	for(int idx = 0; idx < 1000; idx ++)
	{
		for(int jdx = 0; jdx < 1000; jdx ++)
		{
			forest[idx][jdx] = {
					false, none, -1};

		}
	}


}

Forest::~Forest() {

}

int Forest::grow_Forest(double new_tree_prob)
{

	tree_prob = new_tree_prob;

	/*random number generator TODO: TEST!!*/
	std::default_random_engine generator;
	generator.seed(time(NULL));
	std::uniform_int_distribution<int> distribution(0,1);
	int tree_or_not = 0;

	for(int idx = 0; idx < forest_dimension; idx++)
	{
		for(int jdx = 0; jdx < forest_dimension; jdx++)
		{
			/*number between */
			tree_or_not = distribution(generator);
			if(tree_or_not <= tree_prob)
			{
				forest[idx][jdx].tree = true;
				forest[idx][jdx].Tree_Stat = green;
				number_of_trees++;
				number_of_unburnt_trees++;
			}
		}
	}

	this->export_Forest(1);

	return 0;
}


int Forest::iginte_Forest()
{
	int idx = 0;
	int jdx = 0;
	int jdx_T;


	/*keeps track of burning trees*/
	int number_burning_trees = 0;


	/*ignite first row of forest */
	for(jdx = 0; jdx<forest_dimension; jdx++)
	{
		if(forest[idx][jdx].tree)
		{
			forest[idx][jdx].Tree_Stat = burning;
			forest[idx][jdx].ignitionTime = time_step;
			number_burning_trees ++;

		}
	}

	/*TODO: IMPLEMENT BOUNDARY CONDITIONS*/
	do
	{

		/*covers all rows except the last one*/
		for(idx = 0; idx < forest_dimension-1; idx++)
		{



			for(jdx = 0; jdx < forest_dimension; jdx++)
			{
				/*denotes the tree to the RIGHT of the current tree*/
				jdx_T = jdx+1;
				if(jdx==forest_dimension-1)
					jdx_T = 0;

				if(forest[idx][jdx].Tree_Stat == burning)
				{

					/*right-neighboring tree*/
					if(forest[idx][jdx_T].tree && forest[idx][jdx_T].Tree_Stat == green)
					{
						forest[idx][jdx_T].Tree_Stat = burning;
						forest[idx][jdx_T].ignitionTime = time_step;
						number_burning_trees++;

					}
					/*bottom_neighbouring tree*/
					if(forest[idx+1][jdx].tree && forest[idx+1][jdx].Tree_Stat == green)
					{
						forest[idx+1][jdx].Tree_Stat = burning;
						forest[idx+1][jdx].ignitionTime = time_step;
						number_burning_trees++;

					}
				}

				else if(forest[idx][jdx].Tree_Stat == green)
				{
					if(forest[idx][jdx_T].tree && forest[idx][jdx_T].Tree_Stat == burning)
					{
						forest[idx][jdx].Tree_Stat = burning;
						forest[idx][jdx].ignitionTime = time_step;
						number_burning_trees++;
					}

					if(forest[idx+1][jdx].tree && forest[idx+1][jdx].Tree_Stat == burning)
					{
						forest[idx][jdx].Tree_Stat = burning;
						forest[idx][jdx].ignitionTime = time_step;

						if(!(forest[idx][jdx+1].Tree_Stat==burning))
						{
							number_burning_trees++;
						}

					}
				}

				if(forest[idx][jdx].ignitionTime == (time_step-1))
				{
					forest[idx][jdx].Tree_Stat = burnedDown;
					number_burning_trees --;
					number_of_unburnt_trees --;
				}
			}



		}


		/*LAST ROW*/
		for(int jdx = 0; jdx<forest_dimension; jdx++)
		{
			jdx_T = jdx+1;
			if(jdx==forest_dimension-1)
				jdx_T = 0;
			if(forest[idx][jdx].Tree_Stat == burning)
			{
				if(forest[forest_dimension][jdx_T].tree && forest[forest_dimension][jdx_T].Tree_Stat == green)
				{
					forest[forest_dimension][jdx_T].Tree_Stat = burning;
					forest[forest_dimension][jdx_T].ignitionTime = time_step;
					number_burning_trees++;

				}
			}
			else if(forest[idx][jdx].Tree_Stat == green)
			{
				if(forest[idx][jdx_T].tree && forest[idx][jdx_T].Tree_Stat == burning)
				{
					forest[idx][jdx].Tree_Stat = burning;
					forest[idx][jdx].ignitionTime = time_step;
					number_burning_trees++;
				}
			}

			if(forest[idx][jdx].ignitionTime == (time_step-1))
			{
				forest[idx][jdx].Tree_Stat = burnedDown;
				number_burning_trees --;
				number_of_unburnt_trees--;
			}

		}

		this->export_Forest(2);
		/*increases time step*/
		time_step = time_step +1;

	} while(number_burning_trees > 0);


	this->export_Forest(0);

	double p_fract = number_of_unburnt_trees/number_of_trees;

	std::cout << "Probability: " << tree_prob << "-> p: " << std::to_string(p_fract) << std::endl;

	return 0;
}


int Forest::export_Forest(int mode)
{
	std::ofstream forest_file;


	/*after_burn*/
	if(mode == 0)
	{
		forest_file.open("Forest_"+std::to_string(tree_prob)+"_"+"barbecue"+".csv");
		for(int idx = 0; idx < forest_dimension; idx++)
		{
			for(int jdx = 0; jdx < forest_dimension; jdx++)
			{
				if(forest[idx][jdx].tree)
				{
					if(forest[idx][jdx].Tree_Stat == green)
						forest_file << "1" << ",";
					else if(forest[idx][jdx].Tree_Stat == burnedDown )
						forest_file << "0" << ",";

				}
				else
					forest_file << " ,";
			}
			forest_file << "\n";
		}
	}

	/*before burn*/
	else if (mode==1)
	{
		forest_file.open("Forest_"+std::to_string(tree_prob)+"_"+"nicengreen"+".csv");
		for(int idx = 0; idx < forest_dimension; idx++)
		{
			for(int jdx = 0; jdx < forest_dimension; jdx++)
			{
				if(forest[idx][jdx].tree)
					forest_file << "1" << ",";
				else
					forest_file << "0" << ",";
			}
			forest_file << "\n";
		}
	}

	/*Snapshots*/
	else if(mode == 2)
	{
		forest_file.open("Forest_"+std::to_string(tree_prob)+"_"+"SNAP_timestep "+ std::to_string(time_step) +".csv");
		for(int idx = 0; idx < forest_dimension; idx++)
		{
			for(int jdx = 0; jdx < forest_dimension; jdx++)
			{
				if(forest[idx][jdx].tree)
				{
					if(forest[idx][jdx].Tree_Stat == burning)
						forest_file << "burning" << ",";
					else if(forest[idx][jdx].Tree_Stat == green)
						forest_file << "green" << ",";
					else if(forest[idx][jdx].Tree_Stat == burnedDown)
						forest_file << "XXX" << ",";
				}
				else
					forest_file << " ,";
			}
			forest_file << "\n";
		}

	}

	forest_file.close();

	return 0;
}
