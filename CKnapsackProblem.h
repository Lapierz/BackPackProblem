#pragma once
#ifndef CKnapsackProblem_h
#define CKnapsackProblem_h

template <class T> 
class CKnapsackProblem
{
public:
	CKnapsackProblem(
		int iEqNumber,
		int iPopulationSize,
		double *pidTabEqValues,
		double *pidTabEqSizes,
		double dSackSize);
	double dFitness(T *pitTabGenotype);
private:
	int i_eq_number;
	int i_population_size;	
	double d_sack_size;			
	double *pi_dtab_eq_sizes;	 
	double *pi_dtab_eq_values;	
};

#endif // !CIndividual_h
