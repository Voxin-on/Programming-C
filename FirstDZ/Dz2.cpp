#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL,"Russian");
    double T= 3.1415926535;
    //T*=2;
    double step = 0.1;
    double checkPogr = 0.00001;
    bool checkPer = true;

    for (double x = 0; x <= 5 * T;x+=step) {
        /*double y1 = sin(x)* sin(x);
        double y2 = sin(x+T)*sin(x+T);*/
        double y1 = tan(x);
        double y2 = tan(x+T);
        /*double y1 = (1/x)*sin(x);
        double y2 = (1 / x) * sin(x+T);*/
        if (isnan(y1) || isnan(y2) || isinf(y1) || isinf(y2)) {
            continue;
        }
        if (fabs(y1-y2)>checkPogr) {
            checkPer = false;
            break;
        }
    }

    if (checkPer) {
        cout << "Переодическая";
    }
    else {
        cout << "Не переодическая";
    }
    return 0;
}