#include "SeedGenerator.h"
#include <chrono>
#include <thread>
#include <utility>

void SeedFunction()
{}

std::seed_seq GenerateRandomSeed()
{
    static uint64_t seed_counter = 0;
    int foo;
    int *m = new int;
    delete m;
    std::seed_seq seed{static_cast<uint64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
            static_cast<uint64_t>(reinterpret_cast<intptr_t>(&seed_counter)),
            static_cast<uint64_t>(reinterpret_cast<intptr_t>(&foo)),
            static_cast<uint64_t>(reinterpret_cast<intptr_t>(m)),
            static_cast<uint64_t>(reinterpret_cast<intptr_t>(&SeedFunction)),
            static_cast<uint64_t>(reinterpret_cast<intptr_t>(&_Exit)),
            static_cast<uint64_t>(std::hash<std::thread::id>()(std::this_thread::get_id())),
            ++seed_counter};
    return seed;
};