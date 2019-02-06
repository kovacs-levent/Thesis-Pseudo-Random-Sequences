#include "LegendreSymbol.h"

int LegendreSequence::Legendre(const int a, const int p)
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
	if (a % 2 == 0) //TODO: Shift, instead of dividing
	{
		result = Legendre(a/2, p); //Reduction to finding a/2's Legendre symbol, and (a/p)=((a/2)/p)*(2/p)
		//Finding 2's Legendre symbol by the formula: (2/p)=(-1)^((p^2-1)/8), shifting mask bit for division, 
		if(((p*p-1) & 8) != 0)
		{
			result = -result;
		}
	}
	else
	{
		/*Reduction to finding the Legendre symbol in the form:
		(a/p)=(p/a), if p and a are odd, unless a and p are congruent to 3 mod 4, then (a/p)=-(p/a)*/ 
		result = Legendre(p % a, a);
		//If (p-1)*(q-1)/4 is not 0, then the result is -1, otherwise 1
		if(((a-1)*(p-1) & 4) != 0)
		{
			result = -result;
		}
	}
	return result;
}