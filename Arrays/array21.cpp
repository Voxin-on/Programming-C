#include <iostream>
using namespace std;

int findMediana(int *arr, int first, int last);

int main(){
    int n;
    cin >> n;

    int* A=new int[2*n+1];
    for (int i=0;i<2*n+1;i++)cin>>A[i];

    cout<<findMediana(A, 0, 2*n);

    delete[] A;
    
    return 0;
}

int findMediana(int *arr, int first, int last) {
    int i = first, j = last;
    int buf, comp;
    comp = arr[(first + last) / 2];
    do {
        while (arr[i] < comp && i < last)
            i++;
        while (arr[j] > comp && j > first)
            j--;
        if (i <= j) {
            if (arr[i] > arr[j]) {
                buf = arr[i];
                arr[i] = arr[j];
                arr[j] = buf;
            }
            i++;
            j--;
        }
    } while (i <= j);
    
    int mid=(first + last) / 2;

    if (mid<=j)
        return findMediana(arr, first, j);
    else if (mid>=i)
        return findMediana(arr, i, last);
    else return arr[mid];
}