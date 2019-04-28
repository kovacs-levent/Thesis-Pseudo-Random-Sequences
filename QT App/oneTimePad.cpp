#include "oneTimePad.h"
#include <stdint.h>

oneTimePad::oneTimePad() : key()
{}

std::vector<bool> oneTimePad::Encrypt(const std::vector<bool> &seq)
{
    std::vector<bool> result;
    for(uint64_t i = 0; i < seq.size(); i++)
    {
        result.push_back(seq[i]^key[i]);
    }
    return result;
}
