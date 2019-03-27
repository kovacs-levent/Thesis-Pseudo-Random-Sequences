#ifndef DOCUMENTS_MEASURE_H
#define DOCUMENTS_MEASURE_H
#include <vector>
#include <bitset>
#include <stdint.h>

int64_t wellDistributionMeasure(const std::vector<bool> &seq);

int64_t UMeasure(const std::vector<bool> &seq, const uint32_t sum_length, const uint32_t start_pos, const uint32_t step);

long double kNormality(std::vector<bool> &seq, const uint32_t k);

long double normalityMeasure(const std::vector<bool> &seq);

//Adds one to vec<bool> in bitwise addition, needed for listing every k length bit sequence with normality
void vecBoolInc(std::vector<bool> &vec);

uint64_t TMeasure(const std::vector<bool> &seq, const uint32_t max_pos, const std::vector<bool> &subSeq);
/*int32_t correlation(std::vector<bool> &seq);*/

int64_t kCorrelation(const std::vector<bool> &seq, const uint32_t k);

int64_t correlationMeasure(const std::vector<bool> &seq);

uint64_t getMaxSum(const std::vector<bool> &seq, const uint64_t n, const uint32_t k);

void getMax(const std::vector<bool> &seq, const uint64_t n, const uint32_t k, uint64_t* arr, uint32_t &len, uint64_t &max);



#endif //DOCUMENTS_MEASURE_H
