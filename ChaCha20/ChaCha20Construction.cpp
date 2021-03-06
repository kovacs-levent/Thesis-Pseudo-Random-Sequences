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
    Seed(instate);
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
    for(size_t i = 0; i < 16; i++)
    {
        out[i] = state[i] + working_state[i];
    }
    ++state[12];
    return out;
}

void ChaCha20Construction::Seed(const std::vector<uint32_t> &inbuf)
{
    for(int i = 0; i < 16; i++)
    {
        state[i] = inbuf[i];
    }
}

std::vector<bool> ChaCha20Construction::GenerateStream(uint64_t length)
{
    std::vector<bool> output;
    output.resize(length);
    //16*4 (512 bits) bytes is the fixed size of our ChaCha state
    //If the length is bigger than this, then we can append the whole state to the output stream
    uint64_t i = 0;
    std::array<uint32_t, 16> tmp;
    std::bitset<32> bit_seq;
    while(length >= 512)
    {
        tmp = ChaChaRound();
        ///Iterate through the ChaCha output
        for(size_t j = 0; j < 16; j++)
        {
            bit_seq = tmp[j];
            ///Iterate through the 32 bits of one ChaCha state word
            for(uint8_t z = 0; z < 32; z++)
            {
                output[i] = bit_seq[31-z];
                ++i;
            }
        }
        length -= 512;
    }

    if(length)
    {
        uint8_t j = 0;
        tmp = ChaChaRound();
        while(length >= 32)
        {
            bit_seq = tmp[j];
            for(uint8_t z = 0; z < 32; z++)
            {
                output[i] = bit_seq[31-z];
                ++i;
            }
            ++j;
            length -= 32;
        }

        if(length)
        {
            bit_seq = tmp[j];
            for(uint8_t z = 0; z < length; z++)
            {
                output[i] = bit_seq[31-z];
                ++i;
            }
        }
    }
    return output;
}
