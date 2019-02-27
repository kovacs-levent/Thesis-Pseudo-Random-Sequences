#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
#include <stdint.h>
#include <vector>
#include <cmath>
#include <set>

uint64_t ModMul(uint64_t a, uint64_t b, const uint64_t mod);

uint64_t ModPow(uint64_t base, uint64_t exp, const uint64_t mod);

uint64_t ModAdd(uint64_t a,uint64_t b, const uint64_t mod);

uint64_t ModSub(uint64_t a, uint64_t b, const uint64_t mod);

//This function generates a polynomial which has only simple roots in modular arithmetic, poly represented by it's roots
std::set<uint64_t> GenerateSimpleModPoly(const uint64_t modulus, const unsigned int degree);

//Polynomial is represented by it's roots in a set, we need simple polynomials, which only have simple roots
uint64_t ModPolynomValue(const std::set<uint64_t> &poly, const uint64_t mod, uint64_t var);

//We don't want a complete factorization, only every prime factor once
std::vector<uint64_t> GetPrimeFactors(uint64_t n);
#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_MODPOW_H
