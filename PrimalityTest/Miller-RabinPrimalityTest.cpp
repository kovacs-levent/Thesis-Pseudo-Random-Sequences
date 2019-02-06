#include "Miller-RabinPrimalityTest.h"
#include <random>
#include <math.h>
#include <iostream>
#include "ModPow.h"

//n is the number to be tested, k is the number of rounds for the Miller-Rabin algorithm
// We know, that if n is prime, then for any i integer, i^(n-1) = 1 (mod n) (Fermat's little theorem)
bool IsPrime(const uint64_t n, const int k)
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
