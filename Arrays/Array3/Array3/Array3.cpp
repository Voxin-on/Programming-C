#include <iostream>
using namespace std;
int main()
{
    for (int i = 1000;i<=9999;i++) {
        int current = i;
        bool usl = true;
        int numbers[10] = {0};
        while (current > 0){
            int figure = current % 10;
            numbers[figure]++;
            current /= 10;
        }
        for (int i=0; i < 10; i++) {
            if (numbers[i]==2) {
                usl = false;
            }
        }
        if (usl)cout << i << endl;
    }
    return 0;
}