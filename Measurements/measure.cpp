#include "measure.h"

int32_t UMeasure(const std::vector<std::bitset<8> > &seq, const uint32_t sum_length, const uint32_t start_pos, const uint32_t step);
{
    int32_t result = 0;
    uint32_t start_block = start_pos/8;
    uint32_t start_shift = start_pos % 8;
    for(int j = 1; j <= sum_length; j++)
    {
        uint32_t tmp = start_pos + j*step;
        result += seq[tmp/8][tmp % 8];
    }
}