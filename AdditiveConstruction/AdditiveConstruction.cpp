#include "AdditiveConstruction.h"
#include "../Arithmetics/PrimeArithmetic.h"
#include "../Arithmetics/ModArithmetic.h"
#include "../GeneralPRNG/SeedGenerator.h"

bool AdditiveConstruction::AdditiveChar(const uint64_t n, const uint64_t p, const std::set<uint64_t>& poly)
{
    uint64_t tmp = ModPolynomValue(poly, p, n);
    return tmp < p/2;
}

//Generates a prime >= p
uint64_t AdditiveConstruction::GeneratePrime(uint64_t p)
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
    while(!MillerRabinTest(p, NumOfTrialsMillerRabin))
    {
        p += (2 + IsNextDivisibleBy3*2);
        IsNextDivisibleBy3 = !IsNextDivisibleBy3;
    }
    return p;
}

uint64_t AdditiveConstruction::GenerateDegree(const uint64_t p)
{
    std::seed_seq seed = GenerateRandomSeed();
    std::mt19937_64 mersenne_twister(seed);
    uint64_t maxDegree = 5*std::pow(p, 1.0/10.0);
    std::uniform_int_distribution<> uni_distr(2, maxDegree);
    return uni_distr(mersenne_twister);
}

std::vector<bool> AdditiveConstruction::Generate(const uint64_t stream_size, const uint64_t p, const std::set<uint64_t>& poly)
{
    std::vector<bool> stream;
    stream.resize(stream_size);
    for(uint64_t j = 0; j < stream_size; j++)
    {
        stream[j]= AdditiveChar(j, p, poly);
    }
    return stream;
}