#include <iostream>
using namespace std;

int main(){
    int* arr=new int[5];
    
    for (int i=0;i<5;i++)cin>>arr[i];

    int counts[5] = {0};
    for (int i = 0; i < 5; i++) {
        for (int j=0;j<5;j++){
            if (arr[i]==arr[j]) counts[i]++;
        }
    }

    int max1 = 0, max2 = 0;
    for (int i = 0; i < 5; i++) {
        if (counts[i] > max1) {
            max2 = max1;
            max1 = counts[i];
        } else if ((counts[i] > max2 && counts[i] != max1) || (counts[i] > max2 && counts[i] ==2)) {
            max2 = counts[i];
        }
    }

    if (max1 == 5) {
        cout<<1;
    } else if (max1 == 4) {
        cout<<2;
    } else if (max1 == 3 && max2 == 2) {
        cout<<3;
    } else if (max1 == 3) {
        cout<<4;
    } else if (max1 == 2 && max2 == 2) {
        cout<<5;
    } else if (max1 == 2) {
        cout<<6;
    } else {
        cout<<7;
    }

    delete[] arr;

    return 0;
}