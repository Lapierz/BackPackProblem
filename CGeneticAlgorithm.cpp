#include "pch.h"
#include "CGeneticAlgorithm.h"


template<class T>
CGeneticAlgorithm<T>::CGeneticAlgorithm(
	double dTime,
	int iPopulationSize,
	double dCrossProbability,
	double dMutateProbability,
	int iEqNumber,
	double dSackSize,
	double *pidTabEqValues,
	double *pidTabEqSizes)
{
	i_eq_number = iEqNumber;
	i_population_size = iPopulationSize;
	d_sack_size = dSackSize;
	d_time = dTime;
	d_cross_probability = dCrossProbability;
	d_mutate_probability = dMutateProbability;
	pi_dtab_eq_values = pidTabEqValues;
	pi_dtab_eq_sizes = pidTabEqSizes;
	pi_individual_best_genotype = NULL;
	pi_knapsack = NULL;
}

template <class T>
CGeneticAlgorithm<T>::CGeneticAlgorithm() {
	i_eq_number = NULL;
	i_population_size = NULL;
	d_sack_size = NULL;
	d_time = NULL;
	d_cross_probability = NULL;
	d_mutate_probability = NULL;
	pi_dtab_eq_values = NULL;
	pi_dtab_eq_sizes = NULL;
	pi_individual_best_genotype = NULL;
	pi_knapsack = NULL;
	
	

}


template <class T>
CGeneticAlgorithm<T>::~CGeneticAlgorithm() 
{
	delete pi_knapsack;
	delete pi_individual_best_genotype;
	vDeleteVector();
}

template<class T>
bool CGeneticAlgorithm<T>::vStart(
	double dTime,
	int iPopulationSize,
	double dCrossProbability,
	double dMutateProbability,
	int iEqNumber,
	double dSackSize,
	double *dTabEqValues,
	double *dTabEqSizes,
	CIndividual<T> **picBestSpecimen) 
{
	bool b_correct_validate = bCheckValidate(
		dTime,
		iPopulationSize,
		dCrossProbability,
		dMutateProbability,
		iEqNumber,
		dSackSize,
		dTabEqValues,
		dTabEqSizes);
	if (b_correct_validate) 
	{
		CGeneticAlgorithm<T> cGA(
			dTime,
			iPopulationSize,
			dCrossProbability,
			dMutateProbability,
			iEqNumber,
			dSackSize,
			dTabEqValues,
			dTabEqSizes);
		cGA.vGenerateKnapsack();
		cGA.vGeneratePopulation();
		(*picBestSpecimen) = new CIndividual<T>(*cGA.vExecuteKnapsackProblem());
		return true;
	}
	else 
	{
		return false;
	}
}

template<class T>
void CGeneticAlgorithm<T>::vGenerateKnapsack()
{
	pi_knapsack = new CKnapsackProblem<T>(
		i_eq_number,
		i_population_size,
		pi_dtab_eq_values,
		pi_dtab_eq_sizes,
		d_sack_size);
}

template <class T>
void CGeneticAlgorithm<T>::vGeneratePopulation() 
{
	for (int i = 0; i < i_population_size; i++) 
	{
		vec_population.push_back(new CIndividual<T>(
			i_eq_number,
			false,
			pi_knapsack));
	}
}

template<class T>
CIndividual<T>* CGeneticAlgorithm<T>::vExecuteKnapsackProblem()
{
	double d_best_fitness = -1;					
	double d_new_fitness = -1;						
	double i_timestart = clock();
	while(clock()<i_timestart+d_time)
	{
		vCross();
		vMutate();
		d_new_fitness = ciFindBestGenotype()->dFitness();
		if (d_new_fitness > d_best_fitness)
		{
			d_best_fitness = d_new_fitness;
			if (pi_individual_best_genotype == NULL){
				pi_individual_best_genotype = new CIndividual<T>(*ciFindBestGenotype());
			}
			else{
				delete pi_individual_best_genotype;
				pi_individual_best_genotype = new CIndividual<T>(*ciFindBestGenotype());
			}
		}
	}
	return pi_individual_best_genotype;
}

template<class T>
bool CGeneticAlgorithm<T>::bCheckValidate(
	double dTime,
	int iPopulationSize,
	double dCrossProbability,
	double dMutateProbability,
	int iEqNumber,
	double dSackSize,
	double *dTabEqValues,
	double *dTabEqSizes) 
{
	if (dTime <= 0) return false;
	if (iPopulationSize <= 0) return false;
	if (dCrossProbability < 0) return false;
	if (dCrossProbability > 1) return false;
	if (dMutateProbability < 0) return false;
	if (dMutateProbability > 1) return false; 
	if (iEqNumber <= 0) return false; 
	if (dSackSize <= 0) return false;
	for (int i = 0; i < iEqNumber; i++)
	{
		if (dTabEqSizes[i] < 0 || dTabEqValues[i] < 0)
		{
			return false;
		}
	}
	return true;
}

template<class T>
void CGeneticAlgorithm<T>::vDeleteVector()
{
	for (int i = 0; i < (int)vec_population.size(); i++)
	{
		delete vec_population[i];
	}
	vec_population.clear();
}

template <class T>
void CGeneticAlgorithm<T>::vCross()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> rand_probality(0, I_HUNDRED);						
	uniform_int_distribution<> rand_parent_index(0, (i_population_size - 1));	
	uniform_int_distribution<> rand_cut(0, (i_eq_number - 1));					

	vector<CIndividual<T>*> vec_new_population;	
	double d_probability = 0.0;					
	int i_cut_index = 0;							
	
	CIndividual<T> *pi_parent_second=NULL;					
	CIndividual<T> *pi_parent_first=NULL;					
	CIndividual<T> *pi_child_first=NULL;					
	CIndividual<T> *pi_child_second=NULL;					

	
	for (int i = 0; i < (i_population_size / 2); i++)
	{
		vBetterParent(&pi_parent_first);
		vBetterParent(&pi_parent_second);
		
		d_probability = rand_probality(gen);
		d_probability /= (double)I_HUNDRED;

		if (d_probability < d_cross_probability)
		{
			i_cut_index = rand_cut(gen);
			pi_child_first = new CIndividual<T>(i_eq_number, true, pi_knapsack);
			pi_parent_first->vCross(pi_parent_second, pi_child_first, i_cut_index);
			pi_child_second = new CIndividual<T>((*pi_parent_first) + (*pi_parent_second));
		}
		else
		{
			pi_child_first = new CIndividual<T>(*pi_parent_first);
			pi_child_second = new CIndividual<T>(*pi_parent_second);
		}
		vec_new_population.push_back(pi_child_first);
		vec_new_population.push_back(pi_child_second);
	}
	if (i_population_size % 2 == 1)
	{
		vec_new_population.push_back(new CIndividual<T>(*vec_population[rand_parent_index(gen)]));
	}
	vDeleteVector();
	vec_population = vec_new_population;
}

template <class T>
void CGeneticAlgorithm<T>::vMutate()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> rand_probality(0, I_HUNDRED);		
	double d_probability = 0.0;
	
	for (int i = 0; i < i_population_size; i++)
	{
		d_probability = rand_probality(gen) / I_HUNDRED;
		if (d_probability < d_mutate_probability && i%2==0)
		{
			vec_population[i]->vMutate(d_mutate_probability,i_eq_number);
		}
		else {
			(*vec_population[i])++;
		}
	}
}

template <class T>
void CGeneticAlgorithm<T>::vBetterParent(CIndividual<T>  **piParent) 
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> rand_parent_index(0, (i_population_size - 1));

	CIndividual<T> *pi_random_first = vec_population.at(rand_parent_index(gen));
	CIndividual<T> *pi_random_second = vec_population.at(rand_parent_index(gen));

	if (pi_random_first->dFitness() > pi_random_second->dFitness())
	{
		(*piParent)= pi_random_first;
	}
	else 
	{
		(*piParent) = pi_random_second;
	}
}

template <class T>
CIndividual<T>* CGeneticAlgorithm<T>::ciFindBestGenotype()
{
	int i_index_best = 0;
	double d_best_fitness = 0;
	int i_vec_size = (int)vec_population.size();
	for (int i = 0; i < i_vec_size; i++)
	{
		if (vec_population[i]->dFitness() > d_best_fitness)
		{
			d_best_fitness = vec_population[i]->dFitness();
			i_index_best = i;
		}
	}
	return vec_population[i_index_best];
}

template class CGeneticAlgorithm<bool>;
template class CGeneticAlgorithm<int>;
template class CGeneticAlgorithm<double>;