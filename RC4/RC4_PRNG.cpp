#include "RC4_PRNG.h"
#include <algorithm>

RC4_PRNG::RC4_PRNG(const std::string key)
{
    key_size = key.length();
    KeySizeCheck();
    K = key;
}

RC4_PRNG::RC4_PRNG(const char* key)
{
    key_size = strlen(key);
    KeySizeCheck();
    K = key;
}

void RC4_PRNG::Init()
{
    for(unsigned short i = 0; i < 256; ++i)
    {
        S[i] = i;
    }
    std::cout << "Init OK" << std::endl;
}

void RC4_PRNG::Shuffle()
{
    unsigned short j = 0;
    unsigned char tmp;
    for(unsigned short i = 0; i < 256; ++i)
    {
        j = (j+S[i]+K[i % key_size]) % 256;
        tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }
    //std::cout << "Shuffle OK" << std::endl;
}

void RC4_PRNG::KeySizeCheck()
{
    if(key_size > 256)
    {
        std::cerr << "Supplied key for RC4 is too large!" << std::endl;
        throw KEY_LENGTH_ERROR;
    }
}