#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_SEEDGENERATOR_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_SEEDGENERATOR_H
#include <random>

//We only use the address of this function to create entropy from memory allocation
//We use this, because std::random_device isn't producing proper random seed on every computer, since it's implementation defined properties
static void SeedFunction();

//We create entropy from time, memory allocation, thread id and seed counting
std::seed_seq GenerateRandomSeed();

#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_SEEDGENERATOR_H
