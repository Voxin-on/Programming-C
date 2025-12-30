#include <iostream>
#include <locale.h>
using namespace std;

int two(int cur) {
    int count = 0;
    while (cur > 0) {
        count += (cur & 1);
        cur >>= 1;
    }
    return count;
}

int eight(int cur) {
    int count = 0;
    while (cur > 0) {
        count+=(cur&3);
        cur >>=3;
    }
    return count;
}

int main()
{
    setlocale(LC_ALL,"Russian");
    int count = 0;
    const int numberAll = 10000000;
    int current = 1;
    while (current <= numberAll) {
        if (two(current) == eight(current)) count++;
        current++;
    }
    cout <<"Количество таких натуральных чисел " << count;
    
    return 0;
}