#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    double a;
    cin >> a;

    double step = 0.1;
    double checkPogr = 0.000001;
    bool checkCh = true;
    bool checkNech = true;

    for (double x = -a; x <= a;x+=step) {
        /*double y1 = x*x*x*x;
        double y2=( - x) * ( - x)* (-x)* (-x);*/
        /*double y1 = tan(x);
        double y2 = tan(-x);*/
        double y1 = exp(x);
        double y2 = exp(-x);
        if (isnan(y1) || isnan(y2) || isinf(y1) || isinf(y2)) {
            continue;
        }
        if (fabs(y1-y2)>checkPogr) {
            checkCh = false;
        }
        if (fabs(y1+y2)>checkPogr) {
            checkNech = false;
        }
    }
    if (checkCh && checkNech == false) {
        cout << "Чётная";
    }
    else if (checkNech && checkCh == false) {
        cout << "Нечётная";
    }
    else {
        cout << "Ни чётная и ни нечётная";
    }
    return 0;
}