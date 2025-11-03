#include <iostream>
using namespace std;
int main()
{
    int m, n;
    cin >> m>> n;
    int** A = new int* [m]; 
    for (int i = 0; i < m; i++) 
        A[i] = new int[n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    bool check = false;
    for (int i = 0; i < m; i++) {
        check = true;
        int row = A[i][0];
        int c = 0;

        for (int j = 0; j < n; j++) {
            if (row > A[i][j]) {
                row = A[i][j];
                c = j;
            }
        }
        for (int r = 0; r < m; r++) {
            if (A[r][c] > A[i][c]) {
                check = false;
                break;
            }
        }
        if (check) {
            cout << i+1<<" "<< c+1;
            break;
        }
    }
    if (!check) {
        cout << 0;
    }
    
    for (int i = 0; i < m; i++) 
        delete[] A[i]; 
    delete[] A;
}