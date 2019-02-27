#include "ModArithmetic.h"
#include <random>
#include "../GeneralPRNG/SeedGenerator.h"

uint64_t ModMul(uint64_t a, uint64_t b, const uint64_t mod)
{
    int64_t result = 0;
    while (a != 0)
    {
        if(a & 1)
        {
            result = (result + b) % mod;
        }
        a = a >> 1;
        b = (b << 1) % mod;
    }
    return result;
}

uint64_t ModPow(uint64_t base, uint64_t exp, const uint64_t mod)
{
    base = base % mod;
    uint64_t result = 1;
    while (exp > 0)
    {
        if (exp & 1)
        {
            result = ModMul(result, base, mod);
        }
        base = ModMul(base, base, mod);
        exp = exp >> 1;
    }
    return result;
}

uint64_t ModAdd(uint64_t a, uint64_t b, const uint64_t mod)
{
    uint64_t result;
    if(a >= mod)
    {
        a = a % mod;
    }
    if(b >= mod)
    {
        b = b % mod;
    }
    if(b == 0)
    {
        result = a;
    }
    else
    {
        result = ModSub(a, mod-b, mod);
    }
    return result;
}

uint64_t ModSub(uint64_t a, uint64_t b, const uint64_t mod)
{
    uint64_t result;
    if(a >= mod)
    {
        a = a % mod;
    }
    if(b >= mod)
    {
        b = b % mod;
    }
    if(a >= b)
    {
        result = a-b;
    }
    else
    {
        result = mod - b + a;
    }
    return result;
}

bool IsPrimitiveRoot(const uint64_t n, const uint64_t p)
{
    //If n < p, then gcd(n, p) = 1, because p is prime
    if (n >= p) {
        return false;
    }
    bool l = true;
    //It's enough to test for every (p-1)/q number, where q is a prime factor of p-1
    std::vector <uint64_t> PrimeFactors = GetPrimeFactors(p - 1);
    for (std::vector<uint64_t>::iterator it = PrimeFactors.begin(); it != PrimeFactors.end() && l; it++)
    {
        l = (ModPow(n, (p-1)/(*it), p) != 1);
    }
    return l;
}

std::vector<uint64_t> GetPrimeFactors(uint64_t n)
{
    std::vector<uint64_t> v;
    for(uint64_t i = 2; i < sqrt(n); i++)
    {
        if(n % i == 0)
        {
            v.push_back(i);
            n = n/i;
        }
        while(n % i == 0)
        {
            n = n/i;
        }
    }
    if(n > 2)
    {
        v.push_back(n);
    }
    return v;
}

std::set<uint64_t> GenerateSimpleModPoly(const uint64_t modulus, const unsigned int degree)
{
    if(modulus < degree)
    {
        //TODO::Don't generate poly, display error, and give control back
        //Placeholder code until I implement UI
        std::set<uint64_t> nothing;
        return nothing;
    }
    //std::random_device random_dev;
    std::seed_seq seed = GenerateRandomSeed();
    std::mt19937_64 mersenne_twister(seed);
    std::uniform_int_distribution<> uni_distr(0, modulus-1);
    std::set<uint64_t> roots;
    uint64_t m;
    //Generating random numbers until we get degree number of roots, these are going to represent the polynomial
    while(roots.size() != degree)
    {
        m = uni_distr(mersenne_twister);
        roots.insert(m);
    }
    return roots;
}

uint64_t ModPolynomValue(const std::set<uint64_t> &poly, const uint64_t mod, uint64_t var)
{
    uint64_t result = 1;
    std::set<uint64_t>::const_iterator it = poly.begin();
    while(result != 0 && it != poly.end())
    {
        result = ModMul(result, ModSub(*it, var, mod), mod);
        it++;
    }
    return result;
}
