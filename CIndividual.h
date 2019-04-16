#pragma once
#ifndef CIndividual_h
#define CIndividual_h

#include <random>
#include "CKnapsackProblem.h"
#include "CCONST.h"

using namespace std;

template<class T>
class CIndividual
{
public:
	CIndividual(
		int iGenotypeSize,
		bool bFirst,
		CKnapsackProblem<T>* piCKnapsack);
	CIndividual(const CIndividual<T> &cIndividual);
	~CIndividual();
	double dFitness();
	void vCross(
		CIndividual* piParent,
		CIndividual* piChild,
		int iCutIndex);
	void vMutate(double dMutableProb, int eqNumber);
	T* getGenotype();
	void vAddKnapsack(CKnapsackProblem<T> *piCKnapsack);
	void operator++ (int);
	CIndividual<T> operator+(CIndividual<T> &cOther);
	CIndividual<T> operator-(CIndividual<T> &cOther);
private:
	void vGenerateGenotype();
	int  i_genotype_size;
	T*   pi_ttab_genotype;
	CKnapsackProblem<T>* pi_knapsack_problem;
};
#endif // !CIndividual_h
