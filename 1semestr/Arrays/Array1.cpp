#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int* M = new int[n];
    for (int i = 0; i < n; i++)
        cin >> M[i];

    for (int i = n - 1; i >= 0; i--) {
        if (M[i] == 0) {
            M[i] = 1;
            break;
        } else {
            M[i] = 0;
            if (i == 0) {
                cout << "1 ";
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << M[i] << " ";
    }
    
    delete[] M;
    return 0;
}