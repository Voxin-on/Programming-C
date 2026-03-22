#include <iostream>
#include <limits.h>
using namespace std;

const int nFib = 90;
int* foundFib(int& count);

int main()
{
    int count;
    int* p = foundFib(count);
    for (int i = 0;i<count;i++) {
        cout << *(p + i)<<endl;
    }

    delete[] p;

    return 0;
}
    
int* foundFib(int& count) {
    int* arr = new int[nFib];
    arr[0] = arr[1] = 1;
    count=2;
    for (int i = 2;i<nFib;i++) {
        if (arr[i-1]>INT_MAX-arr[i - 2]) {
            break;
        }
        arr[i] = arr[i - 1] + arr[i - 2];
        count++;
    }
    return arr;
};