#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Arithmetics/ModArithmetic.h"
#include "../Arithmetics/PrimeArithmetic.h"

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
}