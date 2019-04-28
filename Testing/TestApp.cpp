#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Arithmetics/ModArithmetic.h"
#include "../Arithmetics/PrimeArithmetic.h"
#include "../LegendreConstruction/LegendreConstruction.h"
#include "../RC4/RC4_PRG.h"
#include "../AdditiveConstruction/AdditiveConstruction.h"
#include "../ChaCha20/ChaCha20Construction.h"
#include "../Measurements/measure.h"
#include "../QT App/oneTimePad.h"

TEST_CASE("Miller-Rabin prime test", "")
{
    CHECK(MillerRabinTest(13, 40));
    CHECK(MillerRabinTest(1619, 40));
    CHECK(MillerRabinTest(10120459, 40));
    CHECK(!MillerRabinTest(1561, 40));
    CHECK(!MillerRabinTest(15847, 40));
    CHECK(!MillerRabinTest(274613, 40));
}

TEST_CASE("Prime factorization test","")
{
    std::vector<uint64_t> v = GetPrimeFactors(7140133);
    CHECK(v[0] == 7);
    CHECK(v[1] == 11);
    CHECK(v[2] == 13);
    CHECK(v[3] == 1019);
    CHECK(v.size() == 4);
    v = GetPrimeFactors(35147);
    CHECK(v[0] == 7);
    CHECK(v[1] == 5021);
    CHECK(v.size() == 2);
    v = GetPrimeFactors(84);
    CHECK(v[0] == 2);
    CHECK(v[1] == 3);
    CHECK(v[2] == 7);
    CHECK(v.size() == 3);
    v = GetPrimeFactors(13);
    CHECK(v[0] == 13);
    CHECK(v.size() == 1);
}

TEST_CASE("Primitive root of prime test", "")
{
    CHECK(IsPrimitiveRootOfPrime(3, 7));
    CHECK(IsPrimitiveRootOfPrime(10, 97));
    CHECK(!IsPrimitiveRootOfPrime(7, 157));
    CHECK(!IsPrimitiveRootOfPrime(2, 199));
}

TEST_CASE("Modular multiplication test", "")
{
    CHECK(ModMul(6, 9, 7) == 5);
    CHECK(ModMul(2, 99, 101) == 97);
    CHECK(ModMul(28902, 467, 13) == 10);
}

TEST_CASE("Modular exponentiation test", "")
{
    CHECK(ModPow(4, 7, 15) == 4);
    CHECK(ModPow(3, 13, 23) == 9);
    CHECK(ModPow(9, 156, 7) == 1);
}

TEST_CASE("Modular subtraction test", "")
{
    CHECK(ModSub(5, 4, 7) == 1);
    CHECK(ModSub(3, 1, 101) == 2);
    CHECK(ModSub(3, 5, 101) == 99);
    CHECK(ModSub(10, 3, 5) == 2);
    CHECK(ModSub(2, 9, 11) == 4);
    CHECK(ModSub(138, 217, 13) == 12);
}

TEST_CASE("Modular polinom value test", "")
{
    std::set<uint64_t> s;
    s.insert(10);
    s.insert(5);
    s.insert(7);
    CHECK(ModPolynomValue(s, 13, 5) == 0);
    CHECK(ModPolynomValue(s, 13, 2) == 10);
    CHECK(ModPolynomValue(s, 101, 39) == 40);
    std::set<uint64_t> s2;
    s2.insert(1);
    s2.insert(5);
    CHECK(ModPolynomValue(s2, 101, 3) == 97);
}

TEST_CASE("Legendre construction test","")
{
    LegendreConstruction legendre;
    SECTION("Legendre symbol test")
    {
        CHECK(legendre.LegendreSymbol(28, 7) == 0);
        CHECK(legendre.LegendreSymbol(30, 127) == 1);
        CHECK(legendre.LegendreSymbol(483600, 61) == -1);
        CHECK(legendre.LegendreSymbol(12345, 331) == -1);
    }
    SECTION("Generate valid prime test")
    {
        CHECK(legendre.GenerateValidPrime(100) == 101);
        CHECK(legendre.GenerateValidPrime(200) == 211);
        CHECK(legendre.GenerateValidPrime(20000) == 20029);
    }
    SECTION("Generate test")
    {
        std::set<uint64_t> s;
        s.insert(1);
        s.insert(5);
        std::vector<bool> result = legendre.Generate(10, 101, s);
        CHECK(result[0]);
        CHECK(result[1]);
        CHECK(!result[2]);
        CHECK(result[3]);
        CHECK(!result[4]);
        CHECK(result[5]);
        CHECK(result[6]);
        CHECK(!result[7]);
        CHECK(result[8]);
        CHECK(!result[9]);
        CHECK(result.size() == 10);
    }
}

TEST_CASE("RC4 test", "")
{
    RC4Construction rc;
    rc.SetKey("This is a good key");
    std::vector<bool> result = rc.GenerateStream(10);
    CHECK(!result[0]);
    CHECK(!result[1]);
    CHECK(!result[2]);
    CHECK(result[3]);
    CHECK(result[4]);
    CHECK(result[5]);
    CHECK(result[6]);
    CHECK(result[7]);
    CHECK(!result[8]);
    CHECK(!result[9]);
    CHECK(result.size() == 10);
}

TEST_CASE("Additive construction test", "")
{
    AdditiveConstruction additiveGen;
    std::set<uint64_t> s;
    s.insert(1);
    s.insert(5);
    std::vector<bool> result = additiveGen.Generate(10, 23, s);
    CHECK(result[0]);
    CHECK(result[1]);
    CHECK(!result[2]);
    CHECK(!result[3]);
    CHECK(!result[4]);
    CHECK(result[5]);
    CHECK(result[6]);
    CHECK(!result[7]);
    CHECK(!result[8]);
    CHECK(result[9]);
    CHECK(result.size() == 10);
}

TEST_CASE("ChaCha20 construction test", "")
{
    std::vector<uint32_t> instate = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574,
                                     0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
                                     0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c,
                                     0x00000001, 0x09000000, 0x4a000000, 0x00000000};
    ChaCha20Construction chacha(instate);
    SECTION("Quarter round test")
    {
        uint32_t a = 0x11111111;
        uint32_t b = 0x01020304;
        uint32_t c = 0x9b8d6f43;
        uint32_t d = 0x01234567;
        chacha.QuarterRound(a, b, c, d);
        CHECK(a == 0xea2a92f4);
        CHECK(b == 0xcb1cf8ce);
        CHECK(c == 0x4581472e);
        CHECK(d == 0x5881c4bb);
    }
    std::array<uint32_t, 16> resultstate;
    SECTION("ChaCha round test")
    {
        std::array<uint32_t, 16> state = {0xe4e7f110, 0x15593bd1, 0x1fdd0f50, 0xc47120a3,
                                          0xc7f4d1c7, 0x0368c033, 0x9aaa2204, 0x4e6cd4c3,
                                          0x466482d2, 0x09aa9f07, 0x05d7c214, 0xa2028bd9,
                                          0xd19c12b5, 0xb94e16de, 0xe883d0cb, 0x4e3c50a2};
        chacha.Seed(instate);
        resultstate = chacha.ChaChaRound();
        for(int i = 0; i < 16; i++)
        {
            CHECK(resultstate[i] == state[i]);
        }
    }
    SECTION("ChaCha generation test")
    {
        std::array<uint32_t, 16> state = {0xe4e7f110, 0x15593bd1, 0x1fdd0f50, 0xc47120a3,
                                          0xc7f4d1c7, 0x0368c033, 0x9aaa2204, 0x4e6cd4c3,
                                          0x466482d2, 0x09aa9f07, 0x05d7c214, 0xa2028bd9,
                                          0xd19c12b5, 0xb94e16de, 0xe883d0cb, 0x4e3c50a2};
        chacha.Seed(instate);
        std::vector<bool> result = chacha.GenerateStream(10);
        CHECK(result[0]);
        CHECK(result[1]);
        CHECK(result[2]);
        CHECK(!result[3]);
        CHECK(!result[4]);
        CHECK(result[5]);
        CHECK(!result[6]);
        CHECK(!result[7]);
        CHECK(result[8]);
        CHECK(result[9]);
        CHECK(result.size() == 10);
    }
}

TEST_CASE("Measurements tests", "")
{
    std::vector<bool> seq = {1,1,1,0,0,1,0,1,1};
    CHECK(wellDistributionMeasure(seq) == 3);
    CHECK(normalityMeasure(seq) == 1.5);
    CHECK(kCorrelation(seq, 3) == 6);
}

TEST_CASE("One-time pad test","")
{
    oneTimePad otp;
    std::vector<bool> key = {0, 1, 1, 0, 0, 1, 0};
    std::vector<bool> seq = {1, 0, 1, 0, 1, 1, 0};
    std::vector<bool> expected_result = {1, 1, 0, 0, 1, 0, 0};
    otp.setKey(key);
    std::vector<bool> result = otp.Encrypt(seq);
    for(int i = 0; i < seq.size(); i++)
    {
        CHECK(result[i] == expected_result[i]);
    }
    CHECK(result.size() == 7);
}