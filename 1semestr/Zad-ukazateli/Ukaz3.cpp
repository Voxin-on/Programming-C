#include <iostream>
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    const int n = 80;
    char arr[n+1];
    cin.getline(arr, n+1, '\n');
    int leadNumbers[10] = {0};
    char* parr = arr;
    int* pleadNumbers = leadNumbers;
    int max = 0;
    int maxNumber=-1;

    while (*parr) {
         if (*parr>='0' && *parr<='9')
             (*(pleadNumbers + (*parr - '0')))++;
         parr++;
    }

    for (int i=0;i<10;i++) {
        if (*(pleadNumbers+i) > max) {
            max = *(pleadNumbers + i);
            maxNumber = i;
        }
    }

    if (max == 0)
        cout << "Цифр в строке не найдено";
    else
        cout <<"Максимальное количество раз встречается эта цифра: " << maxNumber;

    return 0;
}
