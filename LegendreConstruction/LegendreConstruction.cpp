#include "LegendreConstruction.h"
#include "../Arithmetics/PrimeArithmetic.h"
#include "../Arithmetics/ModArithmetic.h"
#include "../GeneralPRNG/SeedGenerator.h"
#include <iostream>
#include <vector>
#include <random>

uint64_t LegendreConstruction::GenerateDegree(const uint64_t p)
{
    std::seed_seq seed = GenerateRandomSeed();
    std::mt19937_64 mersenne_twister(seed);
    uint64_t maxDegree = 5*std::pow(p, 1.0/10.0);
    std::uniform_int_distribution<> uni_distr(2, maxDegree);
    return uni_distr(mersenne_twister);
}

int LegendreConstruction::LegendreSymbol(const uint64_t a, const uint64_t p)
{
	if(a == 0)
	{
		return 0;
	}
	if(a == 1)
	{
		return 1;
	}
	int result;
	if ((a & 1) == 0)
	{
		result = LegendreSymbol(a/2, p); //Reduction to finding a/2's Legendre symbol, and (a/p)=((a/2)/p)*(2/p)
		//Finding 2's Legendre symbol by the formula: (2/p)=(-1)^((p^2-1)/8)
		//Division implemented as AND 8
		//If the bit sequence has 1 at 8's position, then it's quotient with 8 is odd, otherwise its even
		if(((p*p-1) & 8) != 0)
		{
			result = -result;
		}
	}
	else
	{
		/*Reduction to finding the Legendre symbol in the form, when a and p are co-primes:
		(a/p)=(-1)^((p-1)*(a-1)/4)*(p/a), alternatively, if p and a are congruent to 3 mod 4, then (a/p)=-(p/a)
		 otherwise, (a/p)=(p/a)*/
		result = LegendreSymbol(p % a, a);
		//Calculating the exponent's parity in the same way as above
		if(((a-1)*(p-1) & 4) != 0)
		{
			result = -result;
		}
	}
	return result;
}

std::vector<bool> LegendreConstruction::Generate(const uint64_t stream_size, const uint64_t p, const std::set<uint64_t>& poly)
{
	std::vector<bool> stream;
	for(uint64_t j = 0; j < stream_size; j++)
    {
	    uint64_t tmp = ModPolynomValue(poly, p, j);
	    if(tmp != 0)
	    {
	        int LegSym = LegendreSymbol(j, p);
            if(LegSym == -1)
            {
                stream.push_back(false);
            }
            else
            {
                stream.push_back(true);
            }
        }
        else
        {
            stream.push_back(true);
        }
	}
	return stream;
}

//Search a prime >=p, and which has 2 as a primitive root
uint64_t LegendreConstruction::GenerateValidPrime(uint64_t p)
{
	if(p % 2 == 0)
	{
		p += 1;
	}
	if(p%3 == 0)
	{
		p += 2;
	}
	//Check whether the next odd number will be divisible by 3, we use this to figure out how should we generate the next prime candidate
	bool IsNextDivisibleBy3 = (p%3 == 1);
	while(!MillerRabinTest(p, NumOfTrialsMillerRabin) || !IsPrimitiveRootOfPrime(2, p))
	{
		p += (2 + IsNextDivisibleBy3*2);
		IsNextDivisibleBy3 = !IsNextDivisibleBy3;
	}
	return p;
}
