#include "pch.h"
#include "CppUnitTest.h"
#include "../lr2_3/BitString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestDefaultConstructor)
        {
            BitString b;

            Assert::AreEqual(0L, b.getHigh());
            Assert::AreEqual(0L, b.getLow());
        }

        // Тест XOR
        TEST_METHOD(TestXOR)
        {
            BitString a(5, 3);
            BitString b(3, 5);

            BitString result = a ^ b;

            unsigned long long expected =
                (static_cast<unsigned long long>(5 ^ 3) << 32)
                | static_cast<unsigned long long>(3 ^ 5);

            Assert::AreEqual(
                expected,
                (static_cast<unsigned long long>(
                    static_cast<unsigned long>(result.getHigh())) << 32)
                | static_cast<unsigned long>(result.getLow())
            );
        }

        // Тест зсуву ліворуч
        TEST_METHOD(TestShiftLeft)
        {
            BitString b(0, 1);

            BitString result = b.shiftLeft(4);

            Assert::AreEqual(0L, result.getHigh());
            Assert::AreEqual(16L, result.getLow());
        }

        // Тест зсуву праворуч
        TEST_METHOD(TestShiftRight)
        {
            BitString b(0, 16);

            BitString result = b.shiftRight(2);

            Assert::AreEqual(0L, result.getHigh());
            Assert::AreEqual(4L, result.getLow());
        }

        // Тест операторів зсуву
        TEST_METHOD(TestShiftOperators)
        {
            BitString b(0, 8);

            BitString left = b << 1;
            BitString right = b >> 1;

            Assert::AreEqual(16L, left.getLow());
            Assert::AreEqual(4L, right.getLow());
        }

        // Тест префіксного інкременту
        TEST_METHOD(TestPrefixIncrement)
        {
            BitString b(0, 10);

            ++b;

            Assert::AreEqual(11L, b.getLow());
        }

        // Тест постфіксного інкременту
        TEST_METHOD(TestPostfixIncrement)
        {
            BitString b(0, 10);

            BitString old = b++;

            Assert::AreEqual(10L, old.getLow());
            Assert::AreEqual(11L, b.getLow());
        }

        // Тест префіксного декременту
        TEST_METHOD(TestPrefixDecrement)
        {
            BitString b(0, 10);

            --b;

            Assert::AreEqual(9L, b.getLow());
        }

        // Тест постфіксного декременту
        TEST_METHOD(TestPostfixDecrement)
        {
            BitString b(0, 10);

            BitString old = b--;

            Assert::AreEqual(10L, old.getLow());
            Assert::AreEqual(9L, b.getLow());
        }

        // Тест зсуву на 64 біти
        TEST_METHOD(TestShiftBy64)
        {
            BitString b(1, 1);

            Assert::AreEqual(
                string(64, '0'),
                b.shiftLeft(64).toString()
            );

            Assert::AreEqual(
                string(64, '0'),
                b.shiftRight(64).toString()
            );
        }
	};
}
