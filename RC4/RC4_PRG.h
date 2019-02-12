#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
#include <string>
#include <iostream>
#include <array>
#include <cstring>
#include <vector>
#include <bitset>

class RC4_PRG
{
public:
    RC4_PRG(const std::string key);
    RC4_PRG(const char* key);
    std::vector<std::bitset<8> > GenerateStream(const int);
private:
    enum Errors {KEY_LENGTH_ERROR};
    void Init();
    void Shuffle();
    void KeySizeCheck();
    unsigned char key_size;
    std::array<std::bitset<8>, 256> S;

    std::string K;
};

#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
