#include "ChaCha20Construction.h"
#include <iostream>
int main() {
    std::vector <uint32_t> vec = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
            0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
            0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
            0x00000001, 0x09000000, 0x4a000000, 0x00000000};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << std::hex << vec[i*4 + j] << " ";
        }
        std::cout << std::endl;
    }
    ChaCha20Construction cr(vec);
    std::array<uint32_t, 16> test = cr.ChaChaRound();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << std::hex << test[i*4 + j] << " ";
        }
        std::cout << std::endl;
    }
    /*uint32_t a = 0x11111111;
    uint32_t b = 0x01020304;
    uint32_t c = 0x9b8d6f43;
    uint32_t d = 0x01234567;
    cr.QuarterRound(a, b, c, d);
    std::cout << std::hex << a << " " << b << " " << c << " " << d;*/
    return 0;
}
