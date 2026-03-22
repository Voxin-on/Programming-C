#include <iostream>

using namespace std;

int main(){
    int m,n;
    cin>>m>>n;
    int* A=new int[m];
    int* B=new int[n];
    int* C=new int[m+n];

    int *pA=A;
    int *pB=B;

    for (int i = 0; i < m; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];

    for(int i=0;i<m+n;i++){
        if (pB==B+n||(pA<A+m && *pA<=*pB))
            C[i]=*pA++;
        else
            C[i]=*pB++;
        cout<<C[i]<<" ";
    }

    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}