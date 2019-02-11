#ifndef THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
#define THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
#include <string>
#include <iostream>
#include <array>
#include <cstring>

class RC4_PRNG
{
public:
    RC4_PRNG(const std::string key);
    RC4_PRNG(const char* key);

    std::array<unsigned char, 256> Generate()
    {
        Init();
        Shuffle();
        return S;
    }

private:
    enum Errors {KEY_LENGTH_ERROR};
    void Init();
    void Shuffle();
    void KeySizeCheck();
    unsigned char key_size;
    std::array<unsigned char, 256> S;
    std::string K;
};

#endif //THESIS_PSEUDO_RANDOM_SEQUENCES_RC4_PRNG_H
