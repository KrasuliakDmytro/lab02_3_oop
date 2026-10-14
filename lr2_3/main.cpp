#include "BitString.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Звичайне розташування двох полів
struct BitStringLayout
{
    long high;
    long low;
};

// Розташування полів з вирівнюванням 1 байт
#pragma pack(push, 1)
struct PackedBitStringLayout
{
    long high;
    long low;
};
#pragma pack(pop)

int main()
{
    try
    {
        cout << "===== CONSTRUCTORS =====\n";

        // 1. Конструктор без аргументів
        BitString b1;
        cout << "Default constructor: " << b1 << '\n';

        // 2. Конструктор ініціалізації
        BitString b2(10, 20);
        cout << "Initialization constructor: " << b2 << '\n';

        // 3. Конструктор копіювання
        BitString b3(b2);
        cout << "Copy constructor: " << b3 << '\n';

        // Присвоєння
        BitString b4;
        b4 = b2;
        cout << "Assignment: " << b4 << "\n\n";

        cout << "===== INIT, GETTERS, SETTERS =====\n";

        BitString b5;
        b5.Init(100, 200);

        cout << "Initial value: " << b5 << '\n';
        cout << "High: " << b5.getHigh() << '\n';
        cout << "Low: " << b5.getLow() << '\n';

        if (b5.setHigh(300))
            cout << "High changed successfully\n";

        if (b5.setLow(400))
            cout << "Low changed successfully\n";

        cout << "After setters: " << b5 << "\n\n";

        cout << "===== INPUT =====\n";

        BitString b6;
        b6.Read();

        cout << "Entered bit string: ";
        b6.Display();

        cout << "\n===== XOR =====\n";

        BitString x1(
            0x12345678L, 0x12345678L
        );

        BitString x2(
            0xFFFFFFFFL, 0x00000000L
        );

        cout << "First:  " << x1 << '\n';
        cout << "Second: " << x2 << '\n';
        cout << "XOR:    " << (x1 ^ x2) << "\n\n";

        cout << "===== SHIFTS =====\n";

        cout << "Original: " << x1 << '\n';
        cout << "Left by 4:  " << x1.shiftLeft(4) << '\n';
        cout << "Right by 4: " << x1.shiftRight(4) << '\n';

        cout << "Operator << : " << (x1 << 4) << '\n';
        cout << "Operator >> : " << (x1 >> 4) << "\n\n";

        cout << "===== INCREMENT AND DECREMENT =====\n";

        BitString counter(0, 10);

        cout << "Initial: " << counter << '\n';

        cout << "Prefix ++:  " << ++counter << '\n';
        cout << "Postfix ++: " << counter++ << '\n';
        cout << "After postfix ++: " << counter << '\n';

        cout << "Prefix --:  " << --counter << '\n';
        cout << "Postfix --: " << counter-- << '\n';
        cout << "After postfix --: " << counter << "\n\n";

        cout << "===== STRING CONVERSION =====\n";

        string text = static_cast<string>(x1);
        cout << "Converted string: " << text << "\n\n";

        cout << "===== ARRAY OF OBJECTS =====\n";

        BitString arr[3] = {
            BitString(),
            BitString(1, 2),
            BitString(x1)
        };

        for (int i = 0; i < 3; i++)
        {
            cout << "arr[" << i << "] = " << arr[i] << '\n';
        }

        cout << "\n===== CLASS SIZE =====\n";

        cout << "Size of BitString: "
            << sizeof(BitString) << " bytes\n";

        cout << "Size without pack(1): "
            << sizeof(BitStringLayout) << " bytes\n";

        cout << "Size with pack(1): "
            << sizeof(PackedBitStringLayout) << " bytes\n";
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
