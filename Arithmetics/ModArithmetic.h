#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
#include <stdint.h>
#include <vector>
#include <cmath>

uint64_t ModMul(uint64_t a, uint64_t b, uint64_t m);

uint64_t ModPow(uint64_t base, uint64_t exp, const uint64_t modulus);

//TODO::Implement generation of polynomial having only simple roots in modular arithmetic
std::vector<uint64_t> GenerateModPoly(const uint64_t modulus, const int degree);

//We don't want a complete factorization, only every prime factor once
std::vector<uint64_t> GetPrimeFactors(uint64_t n);
#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
