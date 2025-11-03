#include <iostream>
using namespace std;
int main()
{
    int arr[1000] = { 2, 3, 7, 9, 0, 0, 0, 0, 0, 0 };
    int *parr = arr;
    int left = 0;
    int right = 999;
    int count=0;
    while (left <= right) {
        int center = (left + right )/ 2;
        if (*(parr + center)!=0) {
            count = center +1;
            left = center +1;
        }
        else {
            right = center -1;
        }
    }
    cout << count;
    return 0;
}