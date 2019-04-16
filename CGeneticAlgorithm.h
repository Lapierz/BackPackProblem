#pragma once
#ifndef CGeneticAlgorithm_h
#define CGeneticAlgorithm_h

#include "CKnapsackProblem.h"
#include "CIndividual.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "CCONST.h"

using namespace std;

template <class T>
class CGeneticAlgorithm
{
public:
	bool vStart(
		double dTime,
		int iPopulationSize,
		double dCrossProbability,
		double dMutateProbability,
		int iEqNumber,
		double dSackSize,
		double *pi_dTabEqValues,
		double *pi_dTabEqSizes,
		CIndividual<T> **pi_cBestSpecimen);
	CGeneticAlgorithm(
		double dTime,
		int iPopulationSize,
		double dCrossProbability,
		double dMutateProbability,
		int iEqNumber,
		double dSackSize,
		double *pi_dTabEqValues,
		double *pi_dTabEqSizes);
	CGeneticAlgorithm();
	~CGeneticAlgorithm();
private:
	CKnapsackProblem<T> *pi_knapsack;				//wskaznik na CKnapsackProblem
	CIndividual<T> *pi_individual_best_genotype;	//wskaznik na CIndividual, ktory posiada najlepszy genotyp 
	double d_time;									//liczba iteracji
	int i_population_size;							//rozmiar populacji
	int i_eq_number;								//liczba rzeczy
	double d_sack_size;								//wielkosc plecaka
	double* pi_dtab_eq_values;						//tablica wartosci rzeczy
	double* pi_dtab_eq_sizes;						//tablica wag rzeczy
	double d_cross_probability;						//prawdopodobienstwo krzyzowania
	double d_mutate_probability;					//prawdopodobienstwo mutacji

	vector<CIndividual<T>*> vec_population;

	void vGenerateKnapsack();
	void vGeneratePopulation();
	void vDeleteVector();
	void vCross();
	void vMutate();
	CIndividual<T>* vExecuteKnapsackProblem();
	bool bCheckValidate(
		double dTime,
		int iPopulationSize, 
		double dCrossProbability,
		double dMutateProbability,
		int iEqNumber, 
		double dSackSize,
		double *pidTabEqValues,
		double *pidTabEqSizes);
	CIndividual<T>* ciFindBestGenotype();
	void vBetterParent(CIndividual<T> **piParent);

};

#endif // !CGeneticAlgorithm
