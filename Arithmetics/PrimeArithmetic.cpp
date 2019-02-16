#include "PrimeArithmetic.h"
#include <random>
#include <math.h>
#include <iostream>

//n is the number to be tested, k is the number of rounds for the Miller-Rabin algorithm
// We know, that if n is prime, then for any i integer, i^(n-1) = 1 (mod n) (Fermat's little theorem)
bool MillerRabinTest(const uint64_t n, const int k)
{
    if(n == 2 || n == 3)
    {
        return true;
    }
    if(n <= 0 || n % 2 == 0)
    {
        return false;
    }
    int s = 0;
    uint64_t r = n-1;
    //Finding r integer, for which (n-1)=r*(2^s), where r is an odd number
    while((r & 1) == 0)
    {
        s += 1;
        r = r / 2;
    }
    std::cout << s << " " << r << std::endl;
    /*A test round consists of: Picking a random number m, in the interval [2,n-1]
    If, m^r != 1 (mod n) and m^((2^j)*r) != -1 (mod n) for all 0 <= j <= s-1, then n is not prime
    otherwise, we can say that n is a strong pseudo-prime to the base m.*/
    std::random_device random_dev;
    std::mt19937 mersenne_twister(random_dev());
    std::uniform_int_distribution<> uni_distr(2, n-1);
    uint64_t m;
    uint64_t x;
    bool l = true;
    for(int i = 0; i < k && l; i++)
    {
        m = uni_distr(mersenne_twister);
        std::cout << m << std::endl;
        x = ModPow(m, r, n);
        std::cout << x << std::endl;
        if (x != 1 && x != (n-1))
        {
            int j = 1;
            while (j < s && x != (n-1) && l)
            {
                x = ModPow(x, 2, n);
                std::cout << x << std::endl;
                if(x == 1)
                {
                    std::cout << "what";
                    l = false;
                }
                j += 1;
            }
            if (x != (n-1))
            {
                std::cout << "what?";
                l = false;
            }
        }
    }
    return l;
}

//We assume that p is prime, due to the function being called only for supposed primes, hence, the Euler totient function is p-1
bool IsPrimitiveRootOfPrime(const uint64_t n, const uint64_t p)
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