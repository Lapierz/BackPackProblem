
#include"pch.h"
#include "CBoolProblem.h"
#include "CGeneticAlgorithm.h"

CBoolProblem::CBoolProblem() {}

CBoolProblem::~CBoolProblem() {}

void CBoolProblem::vRunCommand() 
{

	double *dtab_eg_values = new double[4];
	double *dtab_eq_sizes = new double[4];

	dtab_eg_values[0] = 5;
	dtab_eq_sizes[0] = 4;
	dtab_eg_values[1] = 1;
	dtab_eq_sizes[1] = 1;
	dtab_eg_values[2] = 1;
	dtab_eq_sizes[2] = 3;
	dtab_eg_values[3] = 3;
	dtab_eq_sizes[3] = 2;
	
	CGeneticAlgorithm<bool> start;
	CIndividual<bool> *cBestSpecimen = NULL;
	bool b_valid_data;
	b_valid_data = start.vStart(
		D_TIME_B,
		I_POPULATIONSIZE_B,
		D_CORSSPROBABILITY_B,
		D_MUTATEPROBABILITY_B,
		I_EQNUMBER_B,
		D_SACKSIZE_B,
		dtab_eg_values,
		dtab_eq_sizes,
		&cBestSpecimen);
	if (b_valid_data)
	{
		if (cBestSpecimen != NULL)
		{
			cout << S_BEST_GENO << endl;
			for (int i = 0; i < I_EQNUMBER_B; i++)
			{
				cout << cBestSpecimen->getGenotype()[i] << S_SPACE;
			}
			CKnapsackProblem<bool> *pi_Knapsack = new CKnapsackProblem<bool>(I_EQNUMBER_B,
				I_POPULATIONSIZE_B,
				dtab_eg_values,
				dtab_eq_sizes,
				D_SACKSIZE_B);
			cBestSpecimen->vAddKnapsack(pi_Knapsack);
			cout << S_BEST_SOLUTION << cBestSpecimen->dFitness() << endl;
			delete cBestSpecimen;
			delete pi_Knapsack;
		}
	}
	else
	{
		cout << S_WRONG_VALIDATE;
	}
	delete[] dtab_eg_values;
	delete[] dtab_eq_sizes;
}