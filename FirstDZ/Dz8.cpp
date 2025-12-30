#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    double e;
    cin >> e;
    int n = 1;
    
    while (fabs(pow((1.0+1.0/n),n)-exp(1))>e) {
        n++;
    }
    cout << "При n="<< n <<" исследуемое выражение отличается от е менее чем на " <<e;

    return 0;
}