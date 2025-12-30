#include <iostream>
#include <locale.h>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "russian");
    bool doska[64];
    int sum=0;

    for(int i=0;i<64;i++)doska[i] = rand() % 2;

    cout << "Вы тролль выберите клетку на доске: ";
    int number;
    do {
        cin >> number;
    } while (number < 0 || number > 63);

    for(int i=0;i<64;i++)
        if (doska[i]==1)
            sum^=i;

    int flip=number^sum;
    cout <<"1 программист перевернул эту монету: "<< flip<<endl;
    doska[flip] = !doska[flip];

    sum = 0;

    for(int i=0;i<64;i++)
        if (doska[i]==1)
            sum^=i;

    cout << "2 программист назвал клетку: " << sum << endl;
    cout << (sum == number ? "Программисты сбежали!" : "Вы съели программистов!");

    return 0;
}