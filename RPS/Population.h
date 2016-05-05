#pragma once
#include <vector>
#include <memory>
#include "Individual.h"


#define MUTATE	true
///<summary>
///Population has a list of individuals that evolve
///</summary>
struct Population
{

	int size;
	std::vector< std::shared_ptr<Individual> > individuals;
	double averageFitness;
	std::shared_ptr<Individual> Champion;

	///<summary>
	///generate a random initial population of size  s
	///knowing which player is important to know if the player wins or loses
	///</summary>
	Population(int s, bool isPlayerOne)
	{
		size = s;
		for (int i = 0; i < size; i++)
		{
			individuals.push_back(std::make_shared<Individual>(isPlayerOne));
		}
		Champion = individuals.at(rand() % size);
	}

	///<summary>
	///average fitness of all the individuals in the population
	///</summary>
	void updateAverageFitness()
	{
		double fit = 0;
		for_each(begin(individuals), end(individuals), [&fit](std::shared_ptr<Individual> indiv) {fit += indiv->fitness; });
		averageFitness = fit / individuals.size();
	};

	float averageNumberOfRules()
	{
		float avgRules = 0;
		for_each(individuals.begin(), individuals.end(), [&avgRules](std::shared_ptr<Individual> indiv) { avgRules += indiv->rules.size(); });

		return avgRules / individuals.size();

	}

	float averageAccurucyOfRules()
	{
		float avgRules = 0;
		for_each(individuals.begin(), individuals.end(), [&avgRules](std::shared_ptr<Individual> indiv) { avgRules += indiv->averageScore; });

		return avgRules / individuals.size();
	}
	///<summary>
	///a new generation is produced and the individuals of the population is the new generation
	///parent selection: tournament selection 
	///survival selection: none, generate random individuals to fill the population size
	///new generation = selected parents + randomly generated individuals
	///</summary>
	void evolve()
	{
		std::vector< std::shared_ptr<Individual> > parents;
		//parents.push_back(Champion);		//pass the most fitted individual of the previous generation to the new generation
		int parentsSize = individuals.size() * 0.2;
		//parents tournament selection: pick 3 randomly and select the fittest
		//remove the selected parent from population to maintain diversity
		//add the selected parent to the new generation vector
	//	int called = 0;
		while (parents.size() < parentsSize)
		{
			int index_selected_parent;
			std::shared_ptr<Individual> fittestPlayer;
			for (int i = 0; i < 3; i++)
			{
				int random_position = rand() % individuals.size();
				std::shared_ptr<Individual> tempIndiv = individuals.at(random_position);
				if (fittestPlayer == nullptr)
				{
					fittestPlayer = tempIndiv; index_selected_parent = random_position;
				}
				else if (abs(fittestPlayer->fitness - tempIndiv->fitness) < 0.0001)
				{
					//std::cout << "this is called \n";
					//called++;
					if (tempIndiv->averageScore > fittestPlayer->averageScore)
					{
						fittestPlayer = tempIndiv; index_selected_parent = random_position;
					}
				}
				else if (tempIndiv->fitness > fittestPlayer->fitness)
				{
					fittestPlayer = tempIndiv; index_selected_parent = random_position;
				}
			}

			parents.push_back(fittestPlayer);
			individuals.erase(individuals.begin() + index_selected_parent);
		}
		//std::cout << "this is called  : " << called;
		//generate the new population from parents
		while (parents.size() < size)
		{
			for (int i = 0; i < parentsSize; i++)
			{
				std::shared_ptr<Individual> tempIndiv = parents.at(i);
				parents.push_back(std::make_shared<Individual>(*tempIndiv, MUTATE));
			}
		}

		individuals = parents;
		switchChampion();
		//sort(begin(individuals), end(individuals), less_than_key());
		
//		Champion = individuals.back();
	};

	//MOVE operator()() { updateNextMoves(); return Champion->nextMove; }

	void updateFitnesses()
	{
		for_each(begin(individuals), end(individuals), [](std::shared_ptr<Individual> player) { player->updateFitness(); });
	}
	void updateNextMoves()
	{
		for_each(begin(individuals), end(individuals), [](std::shared_ptr<Individual> player) { player->updateNextMove(); });
		//switchChampion();
	}
	void switchChampion()
	{
		sort(begin(individuals), end(individuals), less_than_key());
		Champion = individuals.back();
	}


};