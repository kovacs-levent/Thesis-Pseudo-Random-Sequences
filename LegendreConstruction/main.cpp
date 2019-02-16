#include "LegendreConstruction.h"
#include "../Arithmetics/PrimeArithmetic.h"
#include <iostream>

int main()
{
	LegendreConstruction ls;
	std::cout << MillerRabinTest(2047, 40);
	std::vector<std::bitset<8> > vec = ls.Generate(100);
    std::vector<std::bitset<8> >::iterator it = vec.begin();
	while(it != vec.end())
    {
	    std::cout << *it;
	    it++;
    }
	return 0;
}