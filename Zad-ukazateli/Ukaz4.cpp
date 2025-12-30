#include <iostream>
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL,"Russian");
    char arr[81];
    cin.getline(arr, 80, '\n');
    
    char help[81];
    char* phelp=help;

    for (int i = 0; *(arr+i) != '\0'; i++) {

        if (*(arr+i) == '(' || *(arr+i) == '[' || *(arr+i) == '{') 
            *(phelp++) = *(arr+i);
        else if (*(arr+i) == ')') {
            if (phelp == help||*(--phelp) != '(') { cout << "Некорректно"; return 0; }
        }
        else if (*(arr+i) == ']') {
            if (phelp == help||*(--phelp) != '[') { cout << "Некорректно"; return 0; }
        }
        else if (*(arr+i) == '}') {
            if (phelp == help||*(--phelp) != '{') { cout << "Некорректно"; return 0; }
        }
    }

    cout << (phelp==help ? "Корректно" : "Некорректно");

    return 0;
}