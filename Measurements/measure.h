#ifndef DOCUMENTS_MEASURE_H
#define DOCUMENTS_MEASURE_H
#include <vector>
#include <bitset>
#include <stdint.h>

int32_t wellDistribution(const std::vector<std::bitset<8> > &seq);

int32_t UMeasure(const std::vector<std::bitset<8> > &seq, const uint32_t sum_length, const uint32_t start_pos, const uint32_t step);

int32_t normality(std::vector<std::bitset<8> > seq);

int32_t correlation(std::vector<std::bitset<8> > seq);

#endif //DOCUMENTS_MEASURE_H
