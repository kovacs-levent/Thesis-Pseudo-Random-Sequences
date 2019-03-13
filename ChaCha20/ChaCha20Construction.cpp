#include "ChaCha20Construction.h"
#include <iostream>

ChaCha20Construction::ChaCha20Construction()
{
    state[0] = 0x61707865;
    state[1] = 0x3320646e;
    state[2] = 0x79622d32;
    state[3] = 0x6b206574;
}

ChaCha20Construction::ChaCha20Construction(const std::vector<uint32_t> &instate)
{
    for(int i = 0; i < 16; i++)
    {
        state[i] = instate[i];
    }
}

void ChaCha20Construction::QuarterRound(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d)
{
    a += b; d ^= a;
    ///16 bit left rotation of d
    d = (d << 16) | (d >> 16);
    c += d; b ^= c;
    ///12 bit left rotation of b
    b = (b << 12) | (b >> 20);
    a += b; d ^= a;
    ///8 bit left rotation
    d = (d << 8) | (d >> 24);
    c += d; b ^= c;
    ///7 bit rotation
    b = (b << 7) | (b >> 25);
}

std::array<uint32_t, 16> ChaCha20Construction::ChaChaRound()
{
    std::array<uint32_t, 16> working_state = state;
    std::array<uint32_t, 16> out;
    for(int i = 0; i < 10; i++)
    {
        //Column rounds
        QuarterRound(working_state[0], working_state[4], working_state[8], working_state[12]);
        QuarterRound(working_state[1], working_state[5], working_state[9], working_state[13]);
        QuarterRound(working_state[2], working_state[6], working_state[10], working_state[14]);
        QuarterRound(working_state[3], working_state[7], working_state[11], working_state[15]);
        //Diagonal rounds
        QuarterRound(working_state[0], working_state[5], working_state[10], working_state[15]);
        QuarterRound(working_state[1], working_state[6], working_state[11], working_state[12]);
        QuarterRound(working_state[2], working_state[7], working_state[8], working_state[13]);
        QuarterRound(working_state[3], working_state[4], working_state[9], working_state[14]);
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << std::hex << working_state[i*4 + j] << " ";
        }
        std::cout << std::endl;
    }
    for(size_t i = 0; i < 16; i++)
    {
        out[i] = state[i] + working_state[i];
    }
    return out;
}