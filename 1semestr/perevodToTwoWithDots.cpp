#include <iostream>
#include <locale>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    double num;
    cin >> num;
    cout << "Двоичное число: ";
    int binValue = 0x40000000;
    while (binValue > num) binValue >>= 1;
    while (binValue > 0)
    {
        if (num >= binValue)
        {
            cout << "1";
            num -= binValue;
        }
        else
            cout << "0";
        binValue >>= 1;
    }
    cout << ".";
    for (int i = 0; i < 24; i++)
    {
        num *= 2;
        cout << (int)num;
        num -= (int)num;
        if (num <= 1e-8)
            break;
    }
    cout << endl; 
    return 0;
}