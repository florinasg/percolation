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
Forest::Forest(int dimension) :  forest_dimension(dimension),root_row(0), time_step(0)
{

	/*IMPORTANT INITIALIZATIONS*/

	p_fract = 0;

	extinction_time = 0;





}

Forest::~Forest() {

}

int Forest::grow_Forest(double new_tree_prob)
{

	time_step = 1;

	number_of_burnt_trees = 0;

	number_of_trees = 0;


	/*standard way to create 2dim array with new*/
	forest = new root*[forest_dimension];
	for(int i = 0; i < forest_dimension; ++i) {
		forest[i] = new root[forest_dimension];
	}

	for(int idx = 0; idx < forest_dimension; idx ++)
	{
		for(int jdx = 0; jdx < forest_dimension; jdx ++)
		{
			forest[idx][jdx] = {
					false, none, -1};

		}
	}

	tree_prob = new_tree_prob;

	/*random number generator*/
	std::default_random_engine generator;
	generator.seed(time(NULL));
	std::uniform_real_distribution<double> distribution(0,1);
	double tree_or_not = 0;

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

			}
		}
	}
	//this->export_Forest(1);
	return 0;
}


int Forest::iginte_Forest()
{
	int idx = 0;
	int jdx = 0;
	int jdx_T;



	/* Keeps track of burning trees */
	int number_burning_trees = 0;




	/* Ignite first row of forest */
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

		/*Covers all rows except the last one*/
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
					if(forest[idx][jdx_T].tree && (forest[idx][jdx_T].Tree_Stat == green))
					{
						forest[idx][jdx_T].Tree_Stat = burning;
						forest[idx][jdx_T].ignitionTime = time_step;
						number_burning_trees++;

					}
					/*bottom_neighbouring tree*/
					if(forest[idx+1][jdx].tree && (forest[idx+1][jdx].Tree_Stat == green))
					{
						forest[idx+1][jdx].Tree_Stat = burning;
						forest[idx+1][jdx].ignitionTime = time_step;
						number_burning_trees++;

					}
				}

				/*GREEN TREE CASE*/
				else if(forest[idx][jdx].Tree_Stat == green)
				{
					if(forest[idx][jdx_T].tree && (forest[idx][jdx_T].Tree_Stat == burning))
					{
						forest[idx][jdx].Tree_Stat = burning;
						forest[idx][jdx].ignitionTime = time_step;
						number_burning_trees++;
					}

					else if(forest[idx+1][jdx].tree && (forest[idx+1][jdx].Tree_Stat == burning))
					{
						forest[idx][jdx].Tree_Stat = burning;
						forest[idx][jdx].ignitionTime = time_step;
						number_burning_trees++;
					}
				}

			}



		}


		/*LAST ROW*/
		for(int jdx = 0; jdx<forest_dimension; jdx++)
		{
			jdx_T = jdx+1;
			if(jdx==forest_dimension-1)
				jdx_T = 0;
			if(forest[forest_dimension-1][jdx].Tree_Stat == burning)
			{
				if(forest[forest_dimension-1][jdx_T].tree && (forest[forest_dimension-1][jdx_T].Tree_Stat == green))
				{
					forest[forest_dimension-1][jdx_T].Tree_Stat = burning;
					forest[forest_dimension-1][jdx_T].ignitionTime = time_step;
					number_burning_trees++;

				}
			}
			else if(forest[forest_dimension-1][jdx].Tree_Stat == green)
			{
				if(forest[forest_dimension-1][jdx_T].tree && (forest[forest_dimension-1][jdx_T].Tree_Stat == burning))
				{
					forest[forest_dimension-1][jdx].Tree_Stat = burning;
					forest[forest_dimension-1][jdx].ignitionTime = time_step;
					number_burning_trees++;
				}
			}



		}

		/*EXTINcTION TIME*/
		for(idx = 0; idx < forest_dimension; idx++)
		{
			for(jdx = 0; jdx < forest_dimension; jdx++)
			{
				if((forest[idx][jdx].tree) && (forest[idx][jdx].Tree_Stat == burning) && (forest[idx][jdx].ignitionTime == (time_step-1)))
				{

					forest[idx][jdx].Tree_Stat = burnedDown;
					number_burning_trees --;
					number_of_burnt_trees++;
				}

			}
		}

		//this->export_Forest(2);

		//std::cout<< forest_dimension <<" time_Step: " << time_step << " number of burning trees: " << number_burning_trees<< std::endl;

		/*Increases Time Step*/
		time_step = time_step +1;

	} while(number_burning_trees > 0);


	/*writes burned forest to file*/
	//this->export_Forest(0);

	/*TODO extinction time line must maybe replaced due to */
	//std::cout << "Single Values: " << number_of_burnt_trees/number_of_trees << " " << time_step << std::endl;

	extinction_time = extinction_time +time_step/(forest_dimension+1);
	p_fract = p_fract + (number_of_burnt_trees/number_of_trees)/(forest_dimension+1);

	//std::cout << "Monte Carlo Step: " << p_fract << " " << extinction_time << std::endl;



	for(int i = 0; i < forest_dimension; ++i) {
		delete [] forest[i];
	}
	delete [] forest;


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
						forest_file << "XXX" << ",";

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


	/*MONTE CARLO -> STANDARD*/
	else if(mode == 3)
	{
		forest_file.open("p_rho_extT_MONTECARLO_"+std::to_string(forest_dimension)+".csv",std::fstream::app);
		forest_file<<tree_prob<<","<<p_fract<<","<<extinction_time<<"\n";
	}

	/*FOR FINDING p_c with tree density -> rho()*/
	else if(mode == 4)
	{
		forest_file.open("rho(L)_"+std::to_string(tree_prob)+".csv",std::fstream::app);
		forest_file<<forest_dimension<<","<<p_fract<<","<<extinction_time<<"\n";
	}

	forest_file.close();

	return 0;
}
