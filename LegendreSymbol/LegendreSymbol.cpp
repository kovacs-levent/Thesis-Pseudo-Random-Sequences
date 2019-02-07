#include "LegendreSymbol.h"

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