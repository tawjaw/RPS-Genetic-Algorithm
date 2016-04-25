#pragma once
#include <vector>
#include "Condition.h"

#define MAX_HISTORY_SAVED	20

//a vector that will contain all the history played by the two players
//the CONDITIONs in the history vector can not have multiple values as every player played a specific move

static std::vector< std::pair<MOVE,MOVE> >History;

//function to save a played move to history vector while mainting a fixed maximum saved moves
void push_History(std::pair<MOVE,MOVE> his)
{
	if (!(History.size() < MAX_HISTORY_SAVED))
		History.erase(History.begin());

	History.push_back(his);
}

//this method is only used to print history and not any condition..
//as a condition in a history can have only one value which is 2 to the power..
void print_History(int past)
{
	if (!History.empty())
	{
		int win = 0;
		int lose = 0;
		if (History.size() < past)
			for_each(begin(History), end(History), [&win, &lose](std::pair<MOVE,MOVE> &his) 
		{
			std::cout << CONDITION_string[(int)log2(static_cast<int>(createCondition(his.first, his.second)))] << std::endl; 
			if (static_cast<int>(createCondition(his.first, his.second)) < pow(2, 3))
				win++;
			else if (static_cast<int>(createCondition(his.first, his.second)) > pow(2, 5))
				lose++;
		});
		else
			for_each(end(History) - past, end(History), [&win, &lose](std::pair<MOVE, MOVE> &his) 
		{
			std::cout << CONDITION_string[(int)log2(static_cast<int>(createCondition(his.first, his.second)))] << std::endl; 
			if (static_cast<int>(createCondition(his.first, his.second)) < pow(2,3))
				win++;
			else if (static_cast<int>(createCondition(his.first, his.second)) > pow(2,5))
				lose++;
		});
		std::cout << "win: " << win << std::endl;
		std::cout << "lose: " << lose << std::endl;
	}
}
