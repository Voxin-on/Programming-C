#include <iostream>
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    const int n = 80;
    char arr[n+1];
    cin.getline(arr, n, '\n');
    char str[n+1];
    char* parr = arr;
    char* pstr = str;

    while (*parr == ' ')
        parr++;

    while (*parr) {
        if (*parr!=' ')
            *pstr++=*parr++;
        else {
            *pstr++ = *parr;
            while (*parr == ' ')
                parr++;
        }
    }

    if (pstr != str && *(pstr - 1) == ' ')
        pstr--;

    *pstr = '\0';
    cout <<"до "<< "(" << arr << ")" << endl;
    cout <<"после "<<"(" << str << ")" << endl;

    return 0;
}
