#include "pch.h"
#include "CIndividual.h"

template<class T>
CIndividual<T>::CIndividual(
	int iGenotypeSize,
	bool bFirst,
	CKnapsackProblem<T>* piCKnapsack) 
{
	pi_ttab_genotype = NULL;
	i_genotype_size = iGenotypeSize;
	pi_knapsack_problem = piCKnapsack;
	if (bFirst)
	{
		pi_ttab_genotype = new T[iGenotypeSize];
		for (int i = 0; i < iGenotypeSize; i++)
		{
			pi_ttab_genotype[i] = (T)0;
		}
	}
	else vGenerateGenotype();
}

template<class T>
CIndividual<T>::CIndividual(const CIndividual<T> &cIndividual)
{
	i_genotype_size = cIndividual.i_genotype_size;
	pi_ttab_genotype = new T[i_genotype_size];
	pi_knapsack_problem = cIndividual.pi_knapsack_problem;
	for (int i = 0; i < i_genotype_size; i++)
	{
		pi_ttab_genotype[i] = cIndividual.pi_ttab_genotype[i];
	}
}

template <class T>
void CIndividual<T>::vAddKnapsack(CKnapsackProblem<T> *piCKnapsack) 
{
	pi_knapsack_problem = piCKnapsack;
}

template<class T>
CIndividual<T>::~CIndividual()
{
	delete pi_ttab_genotype;
}

template<class T>
double CIndividual<T>::dFitness()
{
	return pi_knapsack_problem->dFitness(pi_ttab_genotype);
}


void CIndividual<bool>::vGenerateGenotype()
{
	pi_ttab_genotype = new bool[i_genotype_size];
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	for (int i = 0; i < i_genotype_size; i++)
	{
		if (dis(gen) > D_HALF)
			pi_ttab_genotype[i] = true;
		else
			pi_ttab_genotype[i] = false;
	}
}

template <class T>
void CIndividual<T>::vGenerateGenotype()
{
	pi_ttab_genotype = new T[i_genotype_size];
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 2);
	for (int i = 0; i < i_genotype_size; i++)
	{
		pi_ttab_genotype[i] = (T)dis(gen);
	}
}

template<class T>
T* CIndividual<T>::getGenotype()
{
	return pi_ttab_genotype;
}

void CIndividual<bool>::operator++(int) 
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);

	for (int ii = 0; ii < i_genotype_size; ii++) 
	{
		double d_propability = dis(gen);
		if (d_propability < D_FIXED_PROB) 
		{
			pi_ttab_genotype[ii] = !pi_ttab_genotype[ii];
		}
	}
}

void CIndividual<int>::operator++(int) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);

	for (int ii = 0; ii < i_genotype_size; ii++) 
	{
		double d_propability = dis(gen);
		if (D_HALF <= d_propability) 
		{
			pi_ttab_genotype[ii] = pi_ttab_genotype[ii] + 1;
		}
		else
		{
			pi_ttab_genotype[ii] = abs(pi_ttab_genotype[ii] - 1);
		}
	}
}

void CIndividual<double>::operator++(int) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);

	for (int ii = 0; ii < i_genotype_size; ii++) 
	{
		double d_propability = dis(gen);
		if (D_HALF<=d_propability ) 
		{
			pi_ttab_genotype[ii] = pi_ttab_genotype[ii] + D_FIXED_VALUE_CHANGE;
		}
		else
		{
			pi_ttab_genotype[ii] = abs(pi_ttab_genotype[ii] - D_FIXED_VALUE_CHANGE);
		}
	}
}

template <class T>
void CIndividual<T>::vCross(CIndividual<T>* piParent, CIndividual<T>* piChild, int cut_index)
{
	int i = 0;
	for (; i <= cut_index; i++)
	{
		piChild->getGenotype()[i] = pi_ttab_genotype[i];
	}
	for (; i < i_genotype_size; i++)
	{
		piChild->getGenotype()[i] = piParent->getGenotype()[i];
	}
}

template <class T>
CIndividual<T> CIndividual<T>::operator+(CIndividual<T> &cOther) {
	int i = i_genotype_size;
	int ii = 0;
	CIndividual<T>  ci_obj(i_genotype_size, true, pi_knapsack_problem);
	for (; ii < i_genotype_size / 2; ii++) {
		ci_obj.pi_ttab_genotype[ii] = pi_ttab_genotype[ii];
	}
	for (; ii < i_genotype_size;ii++) {
		ci_obj.pi_ttab_genotype[ii] = cOther.pi_ttab_genotype[ii];
	}
	return ci_obj;
}

template<class T>
void CIndividual<T>::vMutate(double dMutatePropability,int eqNumber)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> rand_cut(1, (eqNumber - 1));
	int cut1 = 0;
	int cut2 = 0;
	do 
	{
		cut1 = rand_cut(gen);
		cut2 = rand_cut(gen);
	} while (cut1 == cut2);

	if (cut1 > cut2) 
	{
		int acc = cut1;
		cut1 = cut2;
		cut2 = acc;
	}

	T* pi_genotype_rev = new T[i_genotype_size];

	for (int i = 0; i < i_genotype_size; i++) 
	{
		pi_genotype_rev[i] = pi_ttab_genotype[(i_genotype_size-1) - i];
	}
	for (int i = cut1; i <= cut2; i++) 
	{
		pi_ttab_genotype[i] = pi_genotype_rev[i];
	}
	delete[] pi_genotype_rev;
}

template <class T>
CIndividual<T> CIndividual<T>::operator-(CIndividual<T> &cOther) {
	int i = i_genotype_size;
	T z;
	CIndividual<T>  ci_obj(i_genotype_size, true, pi_knapsack_problem);
	for (int ii = 0; ii < i_genotype_size ; ii++) {
		if ((z = cOther.pi_ttab_genotype[ii] - pi_ttab_genotype[ii] )> 0)
			ci_obj.pi_ttab_genotype[ii] = z;
		else
			ci_obj.pi_ttab_genotype[ii] = 0;
	}
	return ci_obj;
}


CIndividual<bool> CIndividual<bool>::operator-(CIndividual<bool> &cOther) {
	int i = i_genotype_size;
	CIndividual<bool>  ci_obj(i_genotype_size, true, pi_knapsack_problem);
	for (int ii = 0; ii < i; ii++) {
		ci_obj.pi_ttab_genotype[ii] = pi_ttab_genotype[ii] ^ cOther.pi_ttab_genotype[ii];
	}
	return ci_obj;
}



template class CIndividual<bool>;
template class CIndividual<int>;
template class CIndividual<double>;