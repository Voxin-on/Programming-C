#include <iostream>
using namespace std;
#include <locale.h>
int main()
{
    setlocale(LC_ALL, "Russian");
    const int n = 80;
    char arr[n];
    cin.getline(arr, n, '\n');
    int leadNumbers[10] = {0};
    char* parr = arr;
    int* pleadNumbers = leadNumbers;
    int max = 0;
    int maxNumber;
    while (*parr) {
         if (*parr>='0' && *parr<='9') {
             (*(pleadNumbers + (*parr - '0')))++;
         }
         parr++;
    }
    for (int i=0;i<10;i++) {
        if (*pleadNumbers > max) {
            max = *pleadNumbers;
            maxNumber = i;
        }
        pleadNumbers++;
    }
    if (max == 0) {
        cout << "Цифр в строке не найдено";
    }
    else {
        cout <<"Максимальное количество раз встречается эта цифра: " << max;
    }
    return 0;
}
