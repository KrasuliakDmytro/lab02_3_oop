#include "BitString.h"
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include <sstream>

// Конструктор без аргументів
BitString::BitString() : high(0), low(0)
{
}

// Конструктор ініціалізації
BitString::BitString(long h, long l) : high(h), low(l)
{
}

// Конструктор копіювання
BitString::BitString(const BitString& other)
    : high(other.high), low(other.low)
{
}

// Отримання всіх 64 бітів як одного числа
unsigned long long BitString::getValue() const
{
    unsigned long long h =
        static_cast<uint32_t>(high);

    unsigned long long l =
        static_cast<uint32_t>(low);

    return (h << 32) | l;
}

// Розділення 64-бітового числа на дві частини
void BitString::setValue(unsigned long long value)
{
    uint32_t h = static_cast<uint32_t>(value >> 32);
    uint32_t l = static_cast<uint32_t>(value);

    // Зберігаємо бітові шаблони у двох полях long.
    high = static_cast<long>(static_cast<int32_t>(h));
    low = static_cast<long>(static_cast<int32_t>(l));
}

// Геттери
long BitString::getHigh() const
{
    return high;
}

long BitString::getLow() const
{
    return low;
}

// Сеттери
// Значення повинно поміщатися у 32 біти.
bool BitString::setHigh(long value)
{
    if (value < numeric_limits<int32_t>::min() ||
        value > numeric_limits<int32_t>::max())
    {
        return false;
    }

    high = value;
    return true;
}

bool BitString::setLow(long value)
{
    if (value < numeric_limits<int32_t>::min() ||
        value > numeric_limits<int32_t>::max())
    {
        return false;
    }

    low = value;
    return true;
}

// Ініціалізація
void BitString::Init(long h, long l)
{
    if (!setHigh(h) || !setLow(l))
    {
        throw invalid_argument("Value is outside the 32-bit range");
    }
}

// Введення 64 символів 0 або 1
void BitString::Read()
{
    string bits;

    while (true)
    {
        cout << "Enter 64 bits (0 or 1): ";
        cin >> bits;

        if (bits.size() == 64 &&
            bits.find_first_not_of("01") == string::npos)
        {
            break;
        }

        cout << "Error! Enter exactly 64 bits.\n";
    }

    unsigned long long value = 0;

    for (char bit : bits)
    {
        value = (value << 1) | (bit - '0');
    }

    setValue(value);
}

// Перетворення у рядок із 64 бітів
string BitString::toString() const
{
    string result;
    unsigned long long value = getValue();

    for (int i = 63; i >= 0; --i)
    {
        result += ((value >> i) & 1ULL) ? '1' : '0';
    }

    return result;
}

// Оператор перетворення у string
BitString::operator string() const
{
    return toString();
}

// Виведення на екран
void BitString::Display() const
{
    cout << toString() << '\n';
}

// Присвоєння
BitString& BitString::operator=(const BitString& other)
{
    if (this != &other)
    {
        high = other.high;
        low = other.low;
    }

    return *this;
}

// XOR
BitString operator^(const BitString& a, const BitString& b)
{
    BitString result;
    result.setValue(a.getValue() ^ b.getValue());
    return result;
}

// Зсув ліворуч
BitString BitString::shiftLeft(int count) const
{
    if (count < 0 || count > 64)
    {
        throw invalid_argument("Shift must be from 0 to 64");
    }

    BitString result;

    if (count == 64)
        result.setValue(0);
    else
        result.setValue(getValue() << count);

    return result;
}

// Зсув праворуч
BitString BitString::shiftRight(int count) const
{
    if (count < 0 || count > 64)
    {
        throw invalid_argument("Shift must be from 0 to 64");
    }

    BitString result;

    if (count == 64)
        result.setValue(0);
    else
        result.setValue(getValue() >> count);

    return result;
}

// Оператори зсуву
BitString BitString::operator<<(int count) const
{
    return shiftLeft(count);
}

BitString BitString::operator>>(int count) const
{
    return shiftRight(count);
}

// Префіксний інкремент: +1
BitString& BitString::operator++()
{
    setValue(getValue() + 1);
    return *this;
}

// Постфіксний інкремент: повертає старе значення
BitString BitString::operator++(int)
{
    BitString old(*this);
    ++(*this);
    return old;
}

// Префіксний декремент: -1
BitString& BitString::operator--()
{
    setValue(getValue() - 1);
    return *this;
}

// Постфіксний декремент: повертає старе значення
BitString BitString::operator--(int)
{
    BitString old(*this);
    --(*this);
    return old;
}

// Оператор введення
istream& operator>>(istream& in, BitString& obj)
{
    string bits;

    while (in >> bits)
    {
        if (bits.size() == 64 &&
            bits.find_first_not_of("01") == string::npos)
        {
            unsigned long long value = 0;

            for (char bit : bits)
            {
                value = (value << 1) | (bit - '0');
            }

            obj.setValue(value);
            break;
        }

        cout << "Error! Enter exactly 64 bits (0 or 1): ";

        if (!in.good())
            break;
    }

    return in;
}

// Оператор виведення
ostream& operator<<(ostream& out, const BitString& obj)
{
    return out << obj.toString();
}
