#include "pch.h"
#include "CKnapsackProblem.h"

template <class T>
CKnapsackProblem<T>::CKnapsackProblem(
	int iEqNumber,
	int iPopulationSize,
	double *pidTabEqValues,
	double *pidTabEqSizes,
	double dSackSize) 
{
	i_population_size = iPopulationSize;
	d_sack_size = dSackSize;
	pi_dtab_eq_sizes = pidTabEqSizes;
	pi_dtab_eq_values = pidTabEqValues;
	i_eq_number = iEqNumber;
}

template <class T>
double CKnapsackProblem<T>::dFitness(T *pitTabGenotype)
{
	double d_return_val = 0;
	double d_size = 0;
	for (int ii = 0; ii < i_eq_number; ii++)
	{
		d_return_val += pi_dtab_eq_values[ii] * pitTabGenotype[ii];
		d_size += pi_dtab_eq_sizes[ii] * pitTabGenotype[ii];
	}
	if (d_size <= d_sack_size)
	{
		return d_return_val;
	}
	else
	{
		return 0;
	}
}

template class CKnapsackProblem<bool>;
template class CKnapsackProblem<int>;
template class CKnapsackProblem<double>;
