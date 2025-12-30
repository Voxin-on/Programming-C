#include <iostream>
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    char snils[15];
    cin.getline(snils, 15);
    int sum = 0;
    int numberPos[9] = {9,8,7,6,5,4,3,2,1};
    int j=0;
    bool end = false;
    int endNumber=0;
    int simpleNumber = 0;
    
    for (int i = 0; snils[i] != '\0'; i++) {
        if (snils[i] >= '0' && snils[i] <= '9'&&!end) {
            int ch = snils[i] - '0';
            sum += ch * numberPos[j];
            j++;
            simpleNumber= simpleNumber * 10 + (snils[i] - '0');
        }
        else if (snils[i] >= '0' && snils[i] <= '9' && end) {
            endNumber = endNumber * 10 + (snils[i] - '0');
            simpleNumber = simpleNumber * 10 + (snils[i] - '0');
        }
        else if (snils[i] == ' ') {
            end = true;
        }
        else continue;
    }

    if (sum % 101 == endNumber) {
        cout << "Контрольное число "<<sum<<" — указано верно";
    }
    else {
        cout << "Контрольное число " << sum << " — указано не верно";
    }

    return 0;
}
