#pragma once
#include "Population.h"
#include <fstream>

///<summary>
///coevolution will create two populations of individuals and will play RPS against each other
///as they play both populations will be adapting to each other's moves
///</summary>
std::ofstream output1;
std::ofstream output2;
std::ofstream output3;
std::ofstream output4;
std::ofstream output5;
std::ofstream output6;
std::ofstream output7;
int score1 = 0;
int win1 = 0;
int win2 = 0;
struct Coevolution
{
	Population p1;
	Population p2;
	Coevolution() : p1(50000, true), p2(50000, false) {}
	///<summary>
	///do something
	///</summary>
	void Play()
	{
		output1.open("score.csv");
		output2.open("avgnorules1.csv");
		output3.open("avgnorules2.csv");
		output4.open("avegfitness1.csv");
		output5.open("avegfitness2.csv");
		output6.open("aac1.csv");
		output7.open("aac2.csv");
		int rounds = 0;
		while (rounds < 500)
		{
			rounds++;
			//play 5 rounds and save champions moves in history


			//	p2();
			for (int i = 0; i < 5; i++)
			{
				p1.updateNextMoves();
				p2.updateNextMoves();
				p1.switchChampion();
				p2.switchChampion();
				MOVE p1Move = p1.Champion->nextMove;
				MOVE p2Move = p2.Champion->nextMove;

				
					
					//output2 << win1 << ",";
				//	output3 << win2 << ",";
					//
					//

				
				
				//std::cout << win1 << std::endl;
			//	std::cout << win2 << std::endl;

			//add move to history
				push_History(std::make_pair(p1Move, p2Move));
				if (static_cast<int>(createCondition(p1Move, p2Move) < pow(2, 3)))
					score1++;
				else if (static_cast<int>(createCondition(p1Move, p2Move) > pow(2, 5)))
					score1--;

				output1 << score1 << ",";
				//update the fitnesses of all players in every population based on the champions' moves

				p1.updateFitnesses();
				p2.updateFitnesses();

				p1.updateAverageFitness();
				p2.updateAverageFitness();

				output4 << p1.averageFitness << ",";
				output5 << p2.averageFitness << ",";

				//std::cout << "champion fitness 1:    " << p1.Champion->fitness << std::endl;
				//std::cout << "champion fitness 2:    " << p2.Champion->fitness << std::endl;
				print_History(1);
				std::cout << "average number of rules of population 1:    " << p1.averageNumberOfRules() << std::endl;
				std::cout << "average number of rules of population 2:    " << p2.averageNumberOfRules() << std::endl;
				std::cout << "average fitness 1 : " << p1.averageFitness << std::endl;
				std::cout << "average fitness 2 : " << p2.averageFitness << std::endl;
				output2 << p1.averageNumberOfRules() << ",";
				output3 << p2.averageNumberOfRules() << ",";
				output6 << p1.averageAccurucyOfRules() << ",";
				output7 << p2.averageAccurucyOfRules() << ",";
			}
			//p1.switchChampion();
			//p2.switchChampion();
			
			p1.evolve();
			p2.evolve();
			//system("cls");


			
			


		}
		output1.close();
		output2.close();
		output3.close();
		output4.close();
		output5.close();
		output6.close();
		output7.close();
	}

	//play against human
	void Play2()
	{
		int rounds = 1000;
		while (rounds > 0)
		{
			rounds--;
			for (int i = 0; i < 3; i++)
			{

				MOVE p1Move ;
				MOVE p2Move;
				int input;
				std::cout << "input move ";
				std::cin >> input;
				p2Move = static_cast<MOVE>(input);

				//add move to history
				push_History(std::make_pair(p1Move, p2Move));
				std::cout << "champion fitness 1:    " << p1.Champion->fitness << std::endl;
				//update the fitnesses of all players in every population based on the champions' moves
				p1.updateFitnesses();
				//p2.updateFitnesses();
				
				//p2.evolve();
				p1.updateAverageFitness();
				//p2.updateAverageFitness();

				if (static_cast<int>(createCondition(p1Move, p2Move)) < 5)
				{
					score1++; win1++;
				}
				else if (static_cast<int>(createCondition(p1Move, p2Move)) > 63)
				{
					score1--; win2++;
				}
			/*	output1 << score1 << ",";
				output2 << win1 << ",";
			//	output3 << win2 << ",";
				output4 << p1.averageNumberOfRules() << ",";
				//output5 << p2.averageNumberOfRules() << ",";
				output6 << p1.averageAccurucyOfRules() << ",";
				//output7 << p2.averageAccurucyOfRules() << ",";

				std::cout << "average fitness 1:    " << p1.averageFitness << std::endl;
				//std::cout << "average fitness 2:    " << p2.averageFitness << std::endl;
				std::cout << "champion fitness 1:    " << p1.Champion->fitness << std::endl;
				//std::cout << "champion fitness 2:    " << p2.Champion->fitness << std::endl;
				print_History(1);*/
			}
			
			p1.evolve();
			
			//system("cls");



			

			if (rounds < 10)
				system("Pause");

		}
	}



};