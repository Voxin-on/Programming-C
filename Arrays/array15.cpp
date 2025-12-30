#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;

    int* A=new int[n];
    for (int i=0;i<n;i++)cin>>A[i];

    int maxCount = 0;
    int result = A[0];
    
    for (int i = 0; i < n; i++) {
        int count = 0;

        for (int j = 0; j < n; j++) {
            if (A[i] == A[j]) {
                count++;
            }
        }
        
        if (count > maxCount) {
            maxCount = count;
            result = A[i];
        }
    }

    cout << "Result: " << result << endl;
    
    delete[] A;
    return 0;
}