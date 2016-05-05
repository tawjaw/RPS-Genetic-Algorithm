#pragma once

#include<vector>
#include"Condition.h"
#include<algorithm>

//a rule is defined as a set of history conditions and a move to be played if the conditions are satisfied
//the position of the condition in the rule represents which history position it should satisfies
//the last element in the condition vector would represent the last move that has been played by the two players

typedef std::pair<std::vector<CONDITION>, MOVE> Rule;

//the maximum number of conditions a randomly generated rule can have
//rules will only be randomly generated with the initial population
//as the individuals evolve the rules should become more complex

int maxConditions = 5;

Rule generate_random_Rule()
{
	int random_number_of_conditions = rand() % (maxConditions) + 1; //rule should have atleast one condition
	std::vector<CONDITION> conditions(random_number_of_conditions);
	MOVE move = static_cast<MOVE>(rand() % 3);
	Rule rule(std::make_pair(conditions, move));
	for_each(begin(rule.first), end(rule.first), [](CONDITION &cond) {cond = createCondition(rand() % 3 + 1); });	//create a condition that satisfies maximum 3 history possibilities only
	
	return rule;
}

//TODO score of rule

int get_rule_Score(Rule rule)
{
	int score = 0;
	for_each(begin(rule.first), end(rule.first) , [&score](CONDITION &cdn) { score += getConditionScore(cdn); });
	return score;
	return 0;
}
/*
void print_Rule(Rule &rule)
{
	for_each(rule.begin(), rule.end() - 1, [](RPS &rps) {cout << RPS_string[rps] << " "; });
	cout << ": " << RPS_string[rule.back()] << "  score: " << get_rule_Score(rule) << endl;
}

*/