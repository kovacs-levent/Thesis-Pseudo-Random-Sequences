#include "LegendreSymbol.h"
#include "../Arithmetics/PrimeArithmetic.h"
#include "../Arithmetics/ModArithmetic.h"
#include <iostream>
#include <vector>

int LegendreSequence::Legendre(const uint64_t a, const uint64_t p)
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
		result = Legendre(a/2, p); //Reduction to finding a/2's Legendre symbol, and (a/p)=((a/2)/p)*(2/p)
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
		result = Legendre(p % a, a);
		//Calculating the exponent's parity in the same way as above
		if(((a-1)*(p-1) & 4) != 0)
		{
			result = -result;
		}
	}
	return result;
}

/*std::vector<std::bitset<8> >*/void LegendreSequence::Generate(const uint64_t stream_size)
{
	//First prime candidate, which satisfies the bit_stream_size*2 < p property.
	//Stream_size is given in bytes, that's why we multiply by 16, we add one, to get the first odd number
	uint64_t n = stream_size*16+1;
	uint64_t p = GenerateValidPrime(n);
	std::cout << p;
}

//Search a prime >=p, and which has 2 as a primitive root
uint64_t LegendreSequence::GenerateValidPrime(uint64_t p)
{
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