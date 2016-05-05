#pragma once

#include <vector>
#include <cstdarg>
#include <iostream>
#include <assert.h>
#include <math.h>
#include <algorithm>


#define PLAYERONE	true


///<summary>
///this enum contains all the possible moves that can be played by two players
///in the perspective of the first player:
///win: from 0 to 2
///draw: from 3 to 5
///lose: from 6 to 8
///every member is a value of 2 to the power n, this way we can assign multiple values to one enum
///if a condition satisfies all the win possibilities the bit representation of that condition would be
/// 000000111
///or.. CONDITION m =(RP | PR | SP);
///which can be also cast to an int of max 511
///in this case it is 7
///</summary>

enum CONDITION
{
	NONE = 0,
	//win
	RS = 1 << 0,	// 0x01
	PR = 1 << 1,	// 0x02
	SP = 1 << 2,
	//draw
	RR = 1 << 3,
	PP = 1 << 4,
	SS = 1 << 5,
	//lost
	RP = 1 << 6,
	PS = 1 << 7,
	SR = 1 << 8
};

//operator to CONDITION
CONDITION operator |= (CONDITION &a, CONDITION b) {
	unsigned ai = static_cast<unsigned>(a);
	unsigned bi = static_cast<unsigned>(b);
	ai |= bi;
	return a = static_cast<CONDITION>(ai);
}


//enum to represent the move every player can play
//Rock, Paper, or Scissors

enum MOVE
{
	R,
	P,
	S
};

enum MUTATION : char
{
	Delete,
	Add,
	Modify,
	NoMutation
};

///pass a list of conditions and create one condition that can satisfy them all
CONDITION createCondition(std::initializer_list<CONDITION> list)
{
	CONDITION condition = NONE;
	for (auto elem : list)
	{
		
		condition |= elem;
	}

	return condition;
}


///pass two moves and return the condition representing it.. if m1 = R and m2 = P then RP will be returned 
CONDITION createCondition(MOVE m1, MOVE m2)
{
	if (m1 == R)
	{
		if (m2 == R)
			return RR;
		else if (m2 == P)
			return RP;
		else if (m2 == S)
			return RS;
	}
	else if (m1 == P)
	{
		if (m2 == R)
			return PR;
		else if (m2 == P)
			return PP;
		else if (m2 == S)
			return PS;
	}
	else if (m1 == S)
	{
		if (m2 == R)
			return SR;
		else if (m2 == P)
			return SP;
		else if (m2 == S)
			return SS;
	}
	assert(false);

}

///pass the number of conditions the returned conditions can satisfy and randomly generate the condition.
//NOTE: the random can generate the same condition 3 times which will make the condition satisfy only one possiblity

CONDITION createCondition(int range_of_condition)
{
	assert(range_of_condition > 0);
	CONDITION cdn = NONE;
	for (int i = 0; i < range_of_condition; i++)
		cdn |= createCondition(static_cast<MOVE>(rand() % 3), static_cast<MOVE>(rand() % 3));
	return cdn;
}

int getConditionScore(CONDITION cdn)
{
	int score = 10;
	if (cdn & RP)
		score--;
	if (cdn & RR)
		score--;
	if (cdn & RS)
		score--;
	if (cdn & PR)
		score--;
	if (cdn & PP)
		score--;
	if (cdn & PS)
		score--;
	if (cdn & SR)
		score--;
	if (cdn & SP)
		score--;
	if (cdn & SS)
		score--;

	return score;
}
///strings to easily print the value of the enums .. for debugging purposes 
static const char *MOVE_string[4] = { "R", "P", "S" };
static const char *CONDITION_string[9] = { "RS", "PR", "SP", "RR", "PP", "SS", "RP", "PS", "SR" };

static const char *MUTATION_string[4] = { "Delete", "Add", "Modify", "No Mutation" };

