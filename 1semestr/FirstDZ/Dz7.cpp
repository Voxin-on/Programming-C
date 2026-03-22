#include <iostream>
#include <cmath>;
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    double e;
    cin >> e;
    double x = 1;

    while (fabs(sin(x) / x - 1) > e) {
        x /= 2;
    }

    cout << "Левая часть равенства отличаеться от правой менее чем на " << e << " при x " << x;

    return 0;
}