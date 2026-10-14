#pragma once
#include <iostream>
#include <string>

using namespace std;

class BitString
{
private:
    long high; // Старші 32 біти
    long low;  // Молодші 32 біти

    // Допоміжні методи для роботи з 64 бітами
    unsigned long long getValue() const;
    void setValue(unsigned long long value);

public:
    // Конструктори
    BitString();
    BitString(long high, long low);
    BitString(const BitString& other);

    // Методи доступу
    long getHigh() const;
    long getLow() const;

    bool setHigh(long value);
    bool setLow(long value);

    // Ініціалізація, введення та виведення
    void Init(long high, long low);
    void Read();
    void Display() const;
    string toString() const;

    // Перетворення об'єкта в рядок
    operator string() const;

    // Операції над бітовими рядками
    BitString& operator=(const BitString& other);

    friend BitString operator^(const BitString& a,
        const BitString& b);

    BitString shiftLeft(int count) const;
    BitString shiftRight(int count) const;

    // Оператори зсуву
    BitString operator<<(int count) const;
    BitString operator>>(int count) const;

    // Префіксний та постфіксний інкремент
    BitString& operator++();
    BitString operator++(int);

    // Префіксний та постфіксний декремент
    BitString& operator--();
    BitString operator--(int);

    // Введення та виведення
    friend istream& operator>>(istream& in, BitString& obj);
    friend ostream& operator<<(ostream& out, const BitString& obj);
};
