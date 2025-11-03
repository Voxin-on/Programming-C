#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int indexZ = 0;
    for (int i=0;i<n;i++) {
        if (arr[i]!=0) {
            arr[indexZ] = arr[i];
            indexZ++;
        }
    }
    for (int i= indexZ;i<n;i++) {
        arr[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i];
    }
    delete[] arr;
    return 0;
}