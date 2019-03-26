#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
#include <string>
#include <iostream>
#include <array>
#include <cstring>
#include <vector>
#include <bitset>
#include <stdint.h>

class RC4_PRG
{
public:
    RC4_PRG();
    RC4_PRG(const std::string key);
    RC4_PRG(const char* key);
    std::vector<bool> GenerateStream(const uint64_t);
    void SetKey(const std::string& s)
    {
        key_size = s.length();
        K = s;
    }
private:
    enum Errors {KEY_LENGTH_ERROR};
    void Init();
    void Shuffle();
    void KeySizeCheck();
    unsigned char key_size;
    std::array<uint8_t, 256> S;
    std::string K;
};

#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
