#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_MILLER_RABINPRIMALITYTEST_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_MILLER_RABINPRIMALITYTEST_H
#include <stdint.h>
#include "ModArithmetic.h"

//When generating the stream, we need a prime where 2 is a primitive root mod p
//This function simply checks whether n is a primitive root of p, where p is prime
//If p is not prime, this function's results may not be accurate, because we don't calculate Euler's totient function
//We can assume, that p is prime, because it's tested beforehand by Miller-Rabin, this means that the totient function is p-1
bool IsPrimitiveRootOfPrime(const uint64_t n, const uint64_t p);

bool MillerRabinTest(const uint64_t n, const int k);
#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_MILLER_RABINPRIMALITYTEST_H
