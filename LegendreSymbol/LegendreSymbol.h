#ifndef LEGENDRESYMBOL_H
#define LEGENDRESYMBOL_H
#include <stdint.h>
#include <vector>
#include <bitset>

class LegendreSequence
{
public:
    int Legendre(const uint64_t a, const uint64_t p);
    //When generating the stream, we need a prime where 2 is a primitive root mod p
    //This function simply checks whether n is a primitive root of p, where p is prime
    //If p is not prime, this function's results may not be accurate, because we don't calculate Euler's totient function
    //We can assume, that p is prime, because it's tested beforehand by Miller-Rabin, this means that the totient function is p-1
    uint64_t GenerateValidPrime(const uint64_t n);
    /*std::vector<std::bitset<8> >*/ void Generate(const uint64_t);
private:
    const int NumOfTrialsMillerRabin = 40;
};
#endif /* LEGENDRESYMBOL_H*/