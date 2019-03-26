#ifndef DOCUMENTS_MEASURE_H
#define DOCUMENTS_MEASURE_H
#include <vector>
#include <bitset>
#include <stdint.h>

int64_t wellDistributionMeasure(const std::vector<bool> &seq);

int64_t UMeasure(const std::vector<bool> &seq, const uint32_t sum_length, const uint32_t start_pos, const uint32_t step);

long double kNormality(std::vector<bool> &seq, const uint32_t k);

long double Normality(const std::vector<bool> &seq);

//Adds one to vec<bool> in bitwise addition, needed for listing every k length bit sequence with normality
void vecBoolInc(std::vector<bool> &vec);

uint64_t TMeasure(const std::vector<bool> &seq, const uint32_t max_pos, const std::vector<bool> &subSeq);
/*int32_t correlation(std::vector<bool> &seq);*/

#endif //DOCUMENTS_MEASURE_H
