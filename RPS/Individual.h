#pragma once
#include "Condition.h"
#include "Rule.h"
#include "History.h"
#include <vector>
#include <array>


#define alpha	0.4

int counter_id = 0;
///<summary>
///individual that has the representation and fitness
///</summary>
struct Individual
{
	std::vector<Rule> rules;
	double fitness;
	std::array<float, 4> mutation_parameters;
	bool isPlayerOne;
	MOVE defaultMove;
	MOVE nextMove;
	float averageScore;
	int id;
	//constructor to randomly create an individual
	Individual(bool p) : fitness(0.48 + (float)(rand() % 50 / 1000.0)), defaultMove(static_cast<MOVE>(rand() % 3)), id(counter_id)
	{
		isPlayerOne = p;
		counter_id++;
		//cout << "constructor one is called " << endl;
		mutation_parameters[Delete] = 0.2;
		mutation_parameters[Add] = 0.2;
		mutation_parameters[Modify] = 0.5;
		mutation_parameters[NoMutation] = 0.1;

		int random_number_of_rules = rand() % 20 + 1;
		std::vector<Rule> temp_rules(random_number_of_rules);
		generate(temp_rules.begin(), temp_rules.end(), generate_random_Rule);
		rules = temp_rules;

		updateAverageScore();
	};
	//constructor to create a mutated player from parent with specific mutation type
	Individual(MUTATION mutation_type, const Individual &parent) : fitness(0.48 + (float)(rand() % 50 / 1000.0)), isPlayerOne(parent.isPlayerOne), rules(parent.rules), defaultMove(static_cast<MOVE>(rand() % 3)), id(counter_id)
	{
		counter_id++;
		//cout << "constructor 2 is called " << endl;
		assert(!parent.rules.empty());
		copy(begin(parent.mutation_parameters), end(parent.mutation_parameters), begin(mutation_parameters));

		mutatePlayer(mutation_type);

	}

	//constructor to create a mutated player from parent based on mutation probability
	//if mutate == false then copy individual with no mutation 
	Individual(Individual &parent, bool mutate) : fitness(0.48 + (float)(rand() % 50 / 1000.0)), isPlayerOne(parent.isPlayerOne), rules(parent.rules), defaultMove(static_cast<MOVE>(rand() % 3)), id(counter_id)
	{
		counter_id++;
		//cout << " constructor 3 is called " << endl;
		assert(!parent.rules.empty());
		copy(begin(parent.mutation_parameters), end(parent.mutation_parameters), begin(mutation_parameters));

		if (mutate)
		{
			MUTATION mutation_type;
			//float mutation_ = float(rand() % 100 / 100.0);
			float mutation_ = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		//	std::cout << mutation_ << " ";
			float temp_ = 0;
			for (int i = 0; i < mutation_parameters.size(); i++)
			{
				temp_ += mutation_parameters[i];
				if (mutation_ <= temp_)
				{
					mutation_type = static_cast<MUTATION>(i);
					//std::cout << MUTATION_string[mutation_type] <<std::endl;

					break;
				}

			}

			mutatePlayer(mutation_type);
			updateAverageScore();
		}

	}


	void mutatePlayer(MUTATION mutation_type)
	{
		//cout << "mutation type " << MUTATION_string[mutation_type] << endl;
		MUTATION mutation_type2 = static_cast<MUTATION>(rand() % 4);
		switch (mutation_type)
		{
		case Delete:
			if (rules.size() > 1)
				rules.erase(rules.begin() + (rand() % rules.size()));
			break;
		case Add:
			rules.push_back(generate_random_Rule());
			break;
		case Modify:
			switch (mutation_type2)
			{
				int random_rule;
				int random_position;
			case Delete:
				random_rule = rand() % rules.size();
				if (rules.at(random_rule).first.size() > 1)
				{
					random_position = rand() % (rules.at(random_rule).first.size()+1);
					if (random_position < rules.at(random_rule).first.size())
						rules.at(random_rule).first.erase(rules.at(random_rule).first.begin() + random_position);
					else
						rules.at(random_rule).second = static_cast<MOVE>(rand() % 3);
				}
				break;
			case Add:
				random_rule = rand() % rules.size();
				random_position = rand() % rules.at(random_rule).first.size();
				rules.at(random_rule).first.insert(rules.at(random_rule).first.begin() + random_position, createCondition(rand() % 9 + 1));
				
				break;
			case Modify:
				random_rule = rand() % rules.size();
				random_position = rand() % (rules.at(random_rule).first.size()+1);
				if (random_position < rules.at(random_rule).first.size() )
					rules.at(random_rule).first.at(random_position) = createCondition(rand() % 9 + 1);
				else
					rules.at(random_rule).second = static_cast<MOVE>(rand() % 3);
				break;
			case NoMutation:
				break;
			}
			break;
		case NoMutation:
			break;
			defaultMove = static_cast<MOVE>(rand() % 3);
		}

	}

	///<summary>
	///check if the rule satisfies the history
	///if all conditions in rule are satisfied then return true
	///if the player is not champion then don't look at the last history
	///</summary>
	bool isRuleSatisfied(Rule &rule)
	{
		if (rule.first.size()  > History.size())
				return false;
		for (int i = 0; i < rule.first.size() ; i++)
		{
			if (!(rule.first.at(rule.first.size() - 1 - i) & createCondition(History.at(History.size() - 1 - i).first, History.at(History.size() - 1 - i).second)))
					return false;
		}
		return true;
	
	}

	///<summary>
	///check all the rules that satisfies the history conditions
	///find the most accurate using get_rule_Score
	///and assign the move of that rule so the individual plays it
	///</summary>
	void updateNextMove()
	{
		Rule* ruletemp = nullptr;
		int highestScore = -1;
		for_each(begin(rules), end(rules), [this, &highestScore, &ruletemp](Rule &rule) { if (isRuleSatisfied(rule)) {
			int rulescore = get_rule_Score(rule);
			if (ruletemp != nullptr) { ruletemp = &rule; highestScore = rulescore; }
			else if (rulescore > highestScore) { ruletemp = &rule; highestScore = rulescore; }
			//std::cout << "the new highscore  " << highestScore << std::endl;
		}
		});

		if (ruletemp != nullptr)
		{
			nextMove = ruletemp->second;
		}
		else
		{
			nextMove = defaultMove;
		}

	}

	///<summary>
	///fitness is updated based on reward; fitness =  fitness*(1 - alpha) + reward*alpha
	///the position of conditions in the enum CONDITION is based on the perspective of player one
	///from 0 to 2 win	which gives reward +1
	///and from 6 to 8 lose	which gives reward -1
	///if the player is not player one then reward*(-1)
	///if it is a draw the reward would be 0 for both
	///</summary>
	void updateFitness()
	{
		float reward = 0;
		if (!History.empty())
		{
			if (isPlayerOne)
			{
				if (static_cast<int>(createCondition(nextMove, History.at(History.size() - 1).second)) < pow(2, 3))
				{
					reward = 1; fitness = fitness*(1 - alpha) + reward*alpha;
				}
				else if (static_cast<int>(createCondition(nextMove, History.at(History.size() - 1).second)) > pow(2, 5))
				{
					reward = -1; fitness = fitness*(1 - alpha) + reward*alpha;
				}
				/*else
				{
					reward = -2; fitness = fitness*(1 - alpha) + reward*alpha;
				}*/
				//fitness = fitness*alpha + reward*(1 - alpha);
			}
			else
			{
				if (static_cast<int>(createCondition(History.at(History.size() - 1).first, nextMove)) < pow(2, 3))
				{
					reward = -1; fitness = fitness*(1 - alpha) + reward*alpha;
				}
				else if (static_cast<int>(createCondition(History.at(History.size() - 1).first, nextMove)) > pow(2, 5))
				{
					reward = 1; fitness = fitness*(1 - alpha) + reward*alpha;
				}
			}
			

		}
	}

	//update the average score of all the rules
	//the higher the score the more accurate and complex this individual is
	void updateAverageScore()
	{
		int scoreTemp = 0;
		for_each(begin(rules), end(rules), [&scoreTemp](Rule &rule) {scoreTemp += get_rule_Score(rule); });
		averageScore = scoreTemp / rules.size();
	}


	//return fitness 
	double operator()() { return fitness; }
	bool operator < (const Individual& indiv2) const
	{
		return (fitness < indiv2.fitness);
	}
	bool operator > (const Individual& indiv2) const
	{
		return (fitness > indiv2.fitness);
	}
};


//operator ab
struct less_than_key
{
	inline bool operator() (const std::shared_ptr<Individual> struct1, const std::shared_ptr<Individual> struct2)
	{
		return (struct1->fitness < struct2->fitness);
	}
};