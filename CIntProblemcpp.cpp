
#include"pch.h"
#include "CIntProblem.h"
#include "CGeneticAlgorithm.h"

CIntProblem::CIntProblem() {}

CIntProblem::~CIntProblem() {}

void CIntProblem::vRunCommand()
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

	CGeneticAlgorithm<int> start;
	CIndividual<int> *cBestSpecimen = NULL;
	bool b_valid_data;
	b_valid_data = start.vStart(
		D_TIME_I,
		I_POPULATIONSIZE_I,
		D_CORSSPROBABILITY_I,
		D_MUTATEPROBABILITY_I,
		I_EQNUMBER_I,
		D_SACKSIZE_I,
		dtab_eg_values,
		dtab_eq_sizes,
		&cBestSpecimen);
	if (b_valid_data)
	{
		if (cBestSpecimen != NULL)
		{
			cout << S_BEST_GENO << endl;
			for (int i = 0; i < I_EQNUMBER_I; i++)
			{
				cout << cBestSpecimen->getGenotype()[i] << S_SPACE;
			}
			CKnapsackProblem<int> *pi_Knapsack = new CKnapsackProblem<int>(I_EQNUMBER_I,
				I_POPULATIONSIZE_I,
				dtab_eg_values,
				dtab_eq_sizes,
				D_SACKSIZE_I);
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