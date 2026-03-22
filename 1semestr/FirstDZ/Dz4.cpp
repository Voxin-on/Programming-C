#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    double k, p, r;
    cin >> k >> p>> r;

    int years=0;

    if (k<=0 || p<=0 || p>100 || r<=0) {
        cout << "Некорретные данные"<<endl;
        return 0;
    }

    if (r>k*p/100) {
        while (k > 0){
            k = k * (1 + p / 100.0);
            k =k- r;
            years++;
        }
        cout << "Можно за " << years<< endl;
    }
    else {
        cout << "Нельзя" << endl;
    }

    return 0;
}