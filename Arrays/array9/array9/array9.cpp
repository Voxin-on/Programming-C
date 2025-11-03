#include <iostream>
using namespace std;
int main()
{
    int m;
    cin >> m;
    int* X=new int[m];
    for (int i = 0; i < m; i++)cin>>X[i];
    bool checkLess = true;;
    int current = 1;
    int k = 1;
    for (int i = 0; i < m-1; i++) {
        if (X[i] < X[i + 1] && checkLess) {
            checkLess=false;
            current++;
            if (current > k)k = current;
        }
        else if (X[i] > X[i + 1] && !checkLess) {
            checkLess=true;
            current++;
            if (current > k)k = current;
        }
        else { 
            checkLess = true;
            current = 1; 
        }
    }
    cout << k;
    delete[] X;
    return 0;
}