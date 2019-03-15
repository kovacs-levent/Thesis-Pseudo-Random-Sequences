#include "ChaCha20Construction.h"
#include <iostream>
#include <bitset>

int main() {
    std::vector <uint32_t> vec = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
            0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
            0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
            0x00000002, 0x09000000, 0x4a000000, 0x00000000};
    ChaCha20Construction cr(vec);
    std::array<uint32_t, 16> test = cr.ChaChaRound();

    std::vector<std::bitset<8> > output = cr.GenerateStream(8);
    for(int i = 0; i < output.size(); i++)
    {
        std::cout << output[i];
    }
    /*uint32_t a = 0x11111111;
    uint32_t b = 0x01020304;
    uint32_t c = 0x9b8d6f43;
    uint32_t d = 0x01234567;
    cr.QuarterRound(a, b, c, d);
    std::cout << std::hex << a << " " << b << " " << c << " " << d;*/
    return 0;
}
