#ifndef DOCUMENTS_CHACHAPRNG_H
#define DOCUMENTS_CHACHAPRNG_H
#include <vector>
#include <bitset>
#include <array>
#include <stdint.h>

class ChaCha20Construction
{
public:
    ChaCha20Construction();
    ChaCha20Construction(const std::vector<uint32_t> &inbuf);
    void Seed(const std::vector<uint32_t> &inbuf);
    std::vector<bool> GenerateStream(uint64_t);
    void QuarterRound(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d);
    std::array<uint32_t, 16> ChaChaRound();
    std::array<uint32_t, 16> state;
};

#endif //DOCUMENTS_CHACHAPRNG_H
