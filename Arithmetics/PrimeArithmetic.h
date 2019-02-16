#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_MILLER_RABINPRIMALITYTEST_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_MILLER_RABINPRIMALITYTEST_H
#include <stdint.h>
#include "ModArithmetic.h"

//We assume that p is prime, due to the function being called only for supposed primes, hence, the Euler totient function is p-1
bool IsPrimitiveRootOfPrime(const uint64_t n, const uint64_t p);

bool MillerRabinTest(const uint64_t n, const int k);
#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_MILLER_RABINPRIMALITYTEST_H
