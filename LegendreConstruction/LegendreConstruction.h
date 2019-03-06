#ifndef LEGENDRE_CONSTRUCTION_H
#define LEGENDRE_CONSTRUCTION_H
#include <stdint.h>
#include <vector>
#include <bitset>
#include <set>

class LegendreConstruction
{
public:
    int LegendreSymbol(const uint64_t a, const uint64_t p);
    uint64_t GenerateValidPrime(uint64_t p);
    //Get a random polynomial degree which is in the interval [2, 5*p^1/10]
    uint64_t GenerateDegree(const uint64_t p);
    std::vector<std::bitset<8> > Generate(const uint64_t stream_size);
    std::vector<std::bitset<8> > Generate(const uint64_t stream_size, const uint64_t p, const std::set<uint64_t>& poly);
private:
    const int NumOfTrialsMillerRabin = 40;
};
#endif /* LEGENDRESYMBOL_H*/