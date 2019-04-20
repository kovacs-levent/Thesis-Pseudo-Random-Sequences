#include "RC4_PRG.h"
#include <algorithm>

RC4Construction::RC4Construction()
{
    key_size = 0;
    K = "";
}

void RC4Construction::Init()
{
    for(unsigned int i = 0; i < 256; ++i)
    {
        S[i] = i;
    }
}

void RC4Construction::Shuffle()
{
    unsigned short j = 0;
    for(unsigned short i = 0; i < 256; ++i)
    {
        j = (j+S[i]+(uint8_t)K[i % key_size]) % 256;
        std::swap(S[i], S[j]);
    }
}

std::vector<bool> RC4Construction::GenerateStream(const uint64_t stream_size)
{
    Init();
    Shuffle();
    std::vector<bool> stream;
    stream.resize(stream_size);
    uint8_t i = 0;
    uint8_t j = 0;
    uint64_t n = 0;
    uint64_t length = stream_size-8;
    while(n <= length)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        std::bitset<8> byte(S[(S[i] + S[j]) % 256]);
        for(int z = 0; z < 8; ++z)
        {
            stream[n+z] = byte[z];
        }
        n += 8;
    }
    if(n != stream_size)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        std::bitset<8> byte(S[(S[i] + S[j]) % 256]);
        for(int z = 0; z < stream_size % 8 ; z++)
        {
            stream[n+z] = byte[z];
        }
    }
    return stream;
}
