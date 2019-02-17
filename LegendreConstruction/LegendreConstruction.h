#ifndef LEGENDRE_CONSTRUCTION_H
#define LEGENDRE_CONSTRUCTION_H
#include <stdint.h>
#include <vector>
#include <bitset>

//TODO:: Implement proper way of getting a polynomial with sufficent degree (make a generator for degrees)
class LegendreConstruction
{
public:
    int LegendreSymbol(const uint64_t a, const uint64_t p);
    uint64_t GenerateValidPrime(const uint64_t n);
    std::vector<std::bitset<8> > Generate(const uint64_t);
private:
    const int NumOfTrialsMillerRabin = 40;
};
#endif /* LEGENDRESYMBOL_H*/