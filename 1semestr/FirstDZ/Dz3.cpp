#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;

    for (int y = b; y >= -b; y--) {          
        for (int x = -a; x <= a; x++) {      
            double el = (double)x * x / (a * a) + (double)y * y / (b * b);
            if (el <= 1.0) {
                cout<<"("<< setw(2) << x << "," << setw(2) << y<<")";
            }
            else {
                cout<<setw(7)<< " ";
            }
        }
        cout << endl;
    }
    return 0;
}