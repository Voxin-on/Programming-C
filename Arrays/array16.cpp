#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int m, n;
    cin >> m >> n;

    int** A = new int*[m];
    for (int i = 0; i < m; i++) {
        A[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    int* pos = new int[m];
    for (int i = 0; i < m; i++) pos[i] = 0;

    bool found = false;

    while (pos[0] < n) {
        int target = A[0][pos[0]];
        bool flag = true;

        for (int i = 1; i < m; i++) {
            while (pos[i] < n && A[i][pos[i]] < target) {
                pos[i]++;
            }
            
            if (pos[i] == n || A[i][pos[i]] > target) {
                flag = false;
            }
        }

        if (flag) {
            cout << target << " ";
            found = true;
            
            int current = A[0][pos[0]];
            while (pos[0] < n && A[0][pos[0]] == current) pos[0]++;
        } else {
            pos[0]++;
        }
    }

    if (!found) cout << "НЕТ";

    for (int i = 0; i < m; i++) delete[] A[i];
    delete[] A;
    delete[] pos;

    return 0;
}