
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int* A = new int[n];
    int max=0;
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0;i<n;i++) {
        for (int j=i;j<n;j++) {
            int start = i;
            int end = j;
            bool check = true;
            while (start < end) {
                if (A[start] != A[end]) {
                    check = false;
                    break;
                }
                start++;
                end--;
            }
            if (check && max < j-i+1) {
                max = j - i + 1;
            }
        }
    }
    cout << max;
}
