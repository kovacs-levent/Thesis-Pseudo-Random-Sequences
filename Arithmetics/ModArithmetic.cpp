#include "ModArithmetic.h"

uint64_t ModMul(uint64_t a, uint64_t b, uint64_t m)
{
    int64_t result = 0;
    while (a != 0)
    {
        if(a & 1)
        {
            result = (result + b) % m;
        }
        a = a >> 1;
        b = (b << 1) % m;
    }
    return result;
}

uint64_t ModPow(uint64_t base, uint64_t exp, const uint64_t modulus)
{
    base = base % modulus;
    uint64_t result = 1;
    while (exp > 0)
    {
        if (exp & 1)
        {
            result = ModMul(result, base, modulus);
        }
        base = ModMul(base, base, modulus);
        exp = exp >> 1;
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