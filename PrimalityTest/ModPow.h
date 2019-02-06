#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
#include <stdint.h>

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
#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
