#include "measure.h"
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <cmath>
#include <algorithm>
#include "../Arithmetics/ModArithmetic.h"
#include "../GeneralPRNG/SeedGenerator.h"

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

uint64_t wellDistributionMeasure(const std::vector<bool> &seq)
{
    uint64_t max = 0;
    uint64_t b = 1;
    int64_t a;
    while(b <= seq.size())
    {
        a = 1-b;
        while(a+b <= seq.size())
        {
            uint64_t tBound = ceil((long double)(seq.size()-a)/(long double)b);
            int64_t result = 0;
            for(uint64_t t = 1; t <= tBound; ++t)
            {
                result += 2*seq[a + t*b]-1;
                int64_t tmp = abs(result);
                if(tmp > max)
                {
                    max = tmp;
                }
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
    std::vector<bool> tmpseq;
    std::vector<std::vector<bool> > bitsequences[k+1][k+1];
    for (int i = 0; i <= k; i++)
    {
        bitsequences[i][0].push_back(seq);
        tmpseq.push_back(false);
    }
    for (int i = 1; i <= k; i++)
    {
        for (int n = 1; n <= i; n++)
        {
            // prefix 0 to all combinations of length len-1
            // with n ones
            for (std::vector<bool> v : bitsequences[i - 1][n])
            {
                v.insert(v.begin(), false);
                bitsequences[i][n].push_back(v);
            }

            // prefix 1 to all combinations of length len-1
            // with n-1 ones
            for (std::vector<bool> v : bitsequences[i - 1][n - 1])
            {
                v.insert(v.begin(), true);
                bitsequences[i][n].push_back(v);
            }
        }
    }
    long double max = 0;
    uint64_t maxStart = seq.size() - k + 1;
    for (int n = 0; n <= k; n++)
    {
        for (std::vector<bool> v : bitsequences[k][n])
        {
            for (uint64_t j = 1; j <= maxStart; j++)
            {
                int64_t m = 0;
                uint64_t result = 0;
                while(m < j)
                {
                    bool l = true;
                    for(uint32_t i = 0; l && i < k; i++)
                    {
                        l = seq[m+i] == v[i];
                    }
                    result += l;
                    ++m;
                }
                long double tmp_measure = std::abs((long double)((long double)result - (long double)j/(long double)seq_count));
                if(tmp_measure > max)
                {
                    max = tmp_measure;
                }
            }
        }
    }
    return max;
}

///We can simplify our calculation by not calling kNormality every time
///We simply generate all at most max_k length sequences and calculate a max for those
long double normalityMeasure(const std::vector<bool> &seq)
{
    //Generating at most max_k length bit sequences in bitsequnces vector
    long double max = 0;
    uint64_t max_k = log2((long double)seq.size());
    std::vector<bool> tmpseq;
    std::vector<std::vector<bool> > bitsequences[max_k+1][max_k+1];
    for (int i = 0; i <= max_k; i++)
    {
        bitsequences[i][0].push_back(tmpseq);
        tmpseq.push_back(false);
    }
    for (int i = 1; i <= max_k; i++)
    {
        for (int n = 1; n <= i; n++)
        {
            // prefix 0 to all combinations of length len-1
            // with n ones
            for (std::vector<bool> v : bitsequences[i - 1][n])
            {
                v.insert(v.begin(), false);
                bitsequences[i][n].push_back(v);
            }

            // prefix 1 to all combinations of length len-1
            // with n-1 ones
            for (std::vector<bool> v : bitsequences[i - 1][n - 1])
            {
                v.insert(v.begin(), true);
                bitsequences[i][n].push_back(v);
            }
        }
    }
    //Calcualting maximal value
    for(int j = 1; j <= max_k; ++j)
    {
        for (int n = 0; n <= j; n++)
        {
            uint64_t seq_count = Pow(2, j);
            uint64_t maxStart = seq.size() - j + 1;
            for (std::vector<bool> v : bitsequences[j][n])
            {
                std::vector<int32_t> failTable(v.size()+1);
                failTable[0] = -1;
                uint32_t pos = 1;
                int32_t candidate = 0;
                while(pos < v.size())
                {
                    if(v[pos] == v[candidate])
                    {
                        failTable[pos] = failTable[candidate];
                    }
                    else
                    {
                        failTable[pos] = candidate;
                        candidate = failTable[candidate];
                        while(candidate >= 0 && v[pos] != v[candidate])
                        {
                            candidate = failTable[candidate];
                        }
                    }
                    ++pos;
                    ++candidate;
                }
                failTable[pos] = candidate;
                int32_t k = 0;
                uint64_t i = 0, match_count = 0;
                std::vector<uint32_t> counts(seq.size(), 0);
                while(i < seq.size())
                {
                    if(seq[i] == v[k])
                    {
                        ++k;
                        if(k == j)
                        {
                            ++match_count;
                            counts[i] = match_count;
                            k = failTable[k];
                        }
                        else
                        {
                            counts[i] = match_count;
                        }
                        ++i;
                    }
                    else
                    {
                        counts[i] = match_count;
                        k = failTable[k];
                        if(k < 0)
                        {
                            ++i;
                            ++k;
                        }
                    }
                }
                uint32_t M = 1;
                size_t bound = counts.size() + std::min(0, -j+2);
                for(int n = 0; n  < bound; ++n)
                {
                    long double tmp_measure = std::abs((long double)counts[n] - (long double)M/(long double)seq_count);
                    if(tmp_measure > max)
                    {
                        max = tmp_measure;
                    }
                    ++M;
                }
            }
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
    /*uint64_t max = 0;
    uint64_t* arr = new uint64_t[k];
    std::string bitmask(k, 1);
    uint64_t upperBound = seq.size()-1;
    bitmask.resize(upperBound, 0);
    do
    {
        int j = 0;
        for (int i = 0; i < upperBound; ++i) // [0..N-1] integers
        {
            if (bitmask[i])
            {
                arr[j] = i;
                ++j;
            }
        }
        uint64_t M = 0;
        while(M+arr[k-1] < seq.size())
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
    while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    delete[] arr;
    return max;*/
}

uint64_t kCorrelationApprox(const std::vector<bool> &seq, const uint32_t k, const uint32_t rounds)
{
    uint64_t max = 0;
    uint32_t i = 0;
    while(i < rounds)
    {
        std::seed_seq seed = GenerateRandomSeed();
        std::mt19937_64 mersenne_twister(seed);
        std::vector<uint64_t> steps;
        std::uniform_int_distribution<> uni_distr(0, seq.size()-k);
        steps.push_back(uni_distr(mersenne_twister));
        uint32_t j = 1;
        while(j < k)
        {
            std::uniform_int_distribution<> tmp_distr(steps[j-1]+1, seq.size()-k+j);
            steps.push_back(tmp_distr(mersenne_twister));
            ++j;
        }
        uint64_t M = 0;
        while(M+steps[k-1] < seq.size())
        {
            int sum = 0;
            int z = 0;
            while(z < M)
            {
                int prod_result = 1;
                for(int n = 0; n < k; ++n)
                {
                    prod_result *= 2*seq[z+steps[n]]-1;
                }
                sum += prod_result;
                ++z;
            }
            int abs_sum = abs(sum);
            if(abs_sum > max)
            {
                max = abs_sum;
            }
            ++M;
        }
        ++i;
    }
    return max;
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
