#include <iostream>
#include <string.h>
#include <locale.h>
using namespace std;
int main()
{
    setlocale(LC_ALL,"Russian");
    int max_len;
    cout << "Введите максимальное количество цифр в двоичном числе: ";
    cin >> max_len;
    char *beforeM=new char[max_len+1];
    int figure = 0;
    cout << "Введите число M в двоичной системе: ";
    cin.getline(beforeM, 1, '\n');
    cin.getline(beforeM, max_len+1, '\n');
    if (strlen(beforeM) >max_len) {
        cout << "Число больше чем максимальное количество символов";
        return 0;
    }
    for (int i = 0; beforeM[i] != 0; i++) {
        figure *= 2;
        int d = beforeM[i] - '0';
        if (d < 0 || d>1) {
            cout << "Неправильнные данные";
            return 0;
        }
        figure += d;
    }
    figure++;
    char *afterM=new char[max_len+2];
    afterM[max_len+1] = 0;
    int i=0;
    while (figure > 0) {
        afterM[max_len - i] = (figure % 2) + '0';
        figure /= 2;
        i++;
    }
    cout << "Результат: ";
    for (int j=max_len-i+1; afterM[j]!=0; j++) cout<< afterM[j];
    delete[] beforeM;
    delete[] afterM;
    return 0;
}