#include <iostream>
#include <locale>;
using namespace std;
int main()
{
    setlocale(LC_ALL,"Russian");
    char arr[80];
    cin.getline(arr, 80, '\n');
    char arrScobki[80];
    char* parrScobki=arrScobki;
    bool check = true;
    for (char* parr = arr; *parr != '\0'; parr++) {
        if (*parr == '(' || *parr == '[' || *parr == '{') {
            *parrScobki = *parr;
            parrScobki ++;
        }
        else if (*parr == ')' || *parr == ']' || *parr == '}') {
            if (parrScobki == arrScobki) {
                check = false;
                break;
            }
            parrScobki--;
            if (*parr == ')' && *parrScobki == '(') {
                check = false;
                break;
            }
            else if (*parr == ']' && *parrScobki == '[') {
                check = false;
                break;
            }
            else if (*parr == '}' && *parrScobki == '{') {
                check = false;
                break;
            }
        }
    }
    if (parrScobki == arrScobki&&check==true) {
        cout << "Правильно";
    }
    else {
        cout << "Неправильно";
    }
    return 0;
}