#include <iostream>
using namespace std;
int main()
{
    int countCouple[3] = { 12 * 12,12,1 };
    int result[3] = {0};
    
    int socks;
    cin >> socks;
    
    for (int i = 0; i < 3; i++) {
        result[i] = socks / countCouple[i];
        socks %= countCouple[i];
        cout << result[i] << endl;
    }

    return 0;
};