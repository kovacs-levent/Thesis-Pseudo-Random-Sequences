#include "measure.h"
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <cmath>
#include "../Arithmetics/ModArithmetic.h"

int64_t UMeasure(const std::vector<bool> &seq, const uint64_t sum_length, int64_t start_pos, const uint64_t step)
{
    int64_t result = 0;
    --start_pos;
    for(int j = 1; j <= sum_length; j++)
    {
        result += seq[start_pos + j*step];
    }
    result -= (sum_length - result);
    return result;
}

//TODO: UMeasure doesn't have to be calculated every time, from start on every sum_length, can get max instead.
uint64_t wellDistributionMeasure(const std::vector<bool> &seq)
{
    uint64_t max = 0;
    uint64_t b = 1;
    int64_t a;
    uint64_t t;
    while(b <= seq.size())
    {
        a = 1-b;
        while(a+b <= seq.size())
        {
            t = 1;
            while(a+t*b <= seq.size())
            {
                int64_t tmp = abs(UMeasure(seq, t, a, b));
                if(tmp > max)
                {
                    max = tmp;
                }
                ++t;
            }
            ++a;
        }
        ++b;
    }
    return max;
}

uint64_t TMeasure(const std::vector<bool> &seq, uint64_t max_pos, const std::vector<bool> &subSeq)
{
    --max_pos;
    int64_t n = 0;
    uint64_t result = 0;
    while(n < max_pos)
    {
        bool l = true;
        for(int i = 0; l && i < subSeq.size(); i++)
        {
            l = seq[n+i] == subSeq[i];
        }
        result += l;
        ++n;
    }
    return result;
}

long double kNormality(const std::vector<bool> &seq, const uint32_t k)
{
    const uint64_t seq_count = Pow(2, k);
    std::vector<bool> bitsequence(k, false);
    long double max = 0;
    uint64_t maxStart = seq.size() - k + 1;
    for(uint64_t bit = 0; bit < seq_count; bit++)
    {
        for (uint64_t j = 1; j <= maxStart; j++)
        {
            int64_t n = 0;
            uint64_t result = 0;
            while(n < j)
            {
                bool l = true;
                for(uint32_t i = 0; l && i < k; i++)
                {
                    l = seq[n+i] == bitsequence[i];
                }
                result += l;
                ++n;
            }
            long double tmp_measure = std::abs((long double)((long double)result - (long double)j/(long double)seq_count));
            if(tmp_measure > max)
            {
                max = tmp_measure;
            }
        }
        vecBoolInc(bitsequence);
    }
    return max;
}

long double normalityMeasure(const std::vector<bool> &seq)
{
    uint64_t max_k = log2((long double)seq.size());
    long double max = kNormality(seq, 1);
    for(uint32_t i = 2; i <= max_k; i++)
    {
        long double tmp = kNormality(seq, i);
        if(tmp > max)
        {
            max = tmp;
        }
    }
    return max;
}

void vecBoolInc(std::vector<bool> &vec)
{
    int i = vec.size()-1;
    vec[i] = !vec[i];
    --i;
    while(i >= 0 && vec[i])
    {
        vec[i] = false;
        --i;
    }
    if(i >= 0)
    {
        vec[i] = true;
    }
}

/*TODO: Actually, increasing order doesn't matter, on the result of the measure, simply unique combinations.
    These might be easier to compute. Gotta check on this.*/
uint64_t kCorrelation(const std::vector<bool> &seq, const uint32_t k)
{
    return getMaxSum(seq, seq.size(), k);
}

uint64_t getMaxSum(const std::vector<bool> &seq, const uint64_t n, const uint32_t k)
{
    uint64_t* arr = new uint64_t[k];
    uint32_t len = 0;
    uint64_t max = 0;
    getMax(seq, n, k, arr, len, max);
    delete[] arr;
    return max;
}

void getMax(const std::vector<bool> &seq, const uint64_t n, const uint32_t k, uint64_t* arr, uint32_t &len, uint64_t &max)
{
    if(len == k)
    {
        uint64_t M = 0;
        while(M + arr[k-1] <= seq.size())
        {
            int sum = 0;
            int i = 0;
            while(i < M)
            {
                int prod_result = 1;
                for(int j = 0; j < k; ++j)
                {
                    prod_result *= 2*seq[i+arr[j]]-1;
                }
                sum += prod_result;
                ++i;
            }
            int abs_sum = abs(sum);
            if(abs_sum > max)
            {
                max = abs_sum;
            }
            ++M;
        }
    }
    else
    {
        int i;
        if(len == 0)
        {
            i = 0;
        }
        else
        {
            i = arr[len-1]+1;
        }
        ++len;
        while(i < n)
        {
            arr[len-1] = i;
            getMax(seq, n, k , arr, len ,max);
            ++i;
        }
        --len;
    }
}

/*TODO: Check on unique combinations. May be able to find an easier way to compute at most k size combinations (without starting from scratch every time), use previous results. Parallel computing is also a possibility.*/

uint64_t correlationMeasure(const std::vector<bool> &seq)
{
    uint32_t max_k = log2((long double)seq.size());
    int64_t max = kCorrelation(seq, 1);
    for(uint32_t i = 2; i <= max_k; i++)
    {
        uint64_t tmp = kCorrelation(seq, i);
        if(tmp > max)
        {
            max = tmp;
        }
    }
    return max;
}
