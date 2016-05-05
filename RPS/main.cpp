#include "Rule.h"
#include "Condition.h"
#include <iostream>
#include <time.h>
#include "History.h"
#include "Coevolution.h"
#include <string>
int main()
{
	srand(time(NULL));
	
	Coevolution c;
	c.Play();
	std::cout << "Done";
	getchar();
}