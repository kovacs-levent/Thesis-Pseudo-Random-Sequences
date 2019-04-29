#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
#include <string>
#include <iostream>
#include <array>
#include <cstring>
#include <vector>
#include <bitset>
#include <stdint.h>

class RC4Construction
{
public:
    RC4Construction();
    std::vector<bool> GenerateStream(const uint64_t);
    void SetKey(const std::string& s)
    {
        key_size = s.length();
        K = s;
    }
private:
    void Init();
    void Shuffle();
    unsigned int key_size;
    std::array<uint8_t, 256> S;
    std::string K;
};

#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
