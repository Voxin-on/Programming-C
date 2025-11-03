#include <iostream>
using namespace std;
int main()
{
    int countCouple[3] = { 12 * 12,12,1 };
    int socks;
    cin >> socks;
    int n1 = socks/ countCouple[0];
    socks%= countCouple[0];
    cout << n1<<endl;
    int n2 = socks / countCouple[1];
    socks %= countCouple[1];
    cout << n2 << endl;
    int n3 = socks;
    cout << n3;
};