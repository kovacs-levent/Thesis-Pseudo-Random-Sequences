#include "RC4_PRG.h"
#include <algorithm>

RC4_PRG::RC4_PRG(const std::string key)
{
    key_size = key.length();
    KeySizeCheck();
    K = key;
}

RC4_PRG::RC4_PRG(const char* key)
{
    key_size = strlen(key);
    KeySizeCheck();
    K = key;
}

void RC4_PRG::KeySizeCheck()
{
    if(key_size > 256)
    {
        std::cerr << "Supplied key for RC4 is too large!" << std::endl;
        throw KEY_LENGTH_ERROR;
    }
}

void RC4_PRG::Init()
{
    for(unsigned short i = 0; i < 256; ++i)
    {
        S[i] = i;
    }
    //std::cout << "Init OK" << std::endl;
}

void RC4_PRG::Shuffle()
{
    unsigned short j = 0;
    unsigned char tmp;
    for(unsigned short i = 0; i < 256; ++i)
    {
        j = (j+S[i].to_ulong()+K[i % key_size]) % 256;
        std::swap(S[i], S[j]);
    }
    //std::cout << "Shuffle OK" << std::endl;
}

std::vector<std::bitset<8> > RC4_PRG::GenerateStream(const u_int64 stream_size)
{
    Init();
    Shuffle();
    std::vector<std::bitset<8> > stream;
    short i = 0;
    short j = 0;
    int n = 0;
    while(n < stream_size)
    {
        i = (i + 1) % 256;
        j = (j + S[i].to_ulong()) % 256;
        std::swap(S[i], S[j]);
        stream.push_back(S[(S[i].to_ulong() + S[j].to_ulong()) % 256]);
        ++n;
    }
    return stream;
}