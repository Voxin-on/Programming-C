#include <iostream>
using namespace std;

int find(int ** A,int i,int j,int m,int n,int count);

int main(){
    int m,n;
    cin>>m>>n;

    int** A=new int*[m];
    for (int i=0;i<m;i++){
        A[i]=new int[n];
        for (int j=0;j<n;j++){
            cin>>A[i][j];
        }
    }

    int result=find(A,0,0,m,n,0);

    cout<<result;

    for (int i = 0; i < m; i++) {
        delete[] A[i];
    }
    delete[] A;

    return 0;
}

int find(int ** A,int i,int j, int m,int n,int count){
    if (i+1>=m) return count;
    if (j+1>=n) return find (A,i+1,0,m,n,count);

    int help[4]={A[i][j],A[i+1][j],A[i][j+1],A[i+1][j+1]};

    if (help[0]==help[1]||help[0]==help[2]||help[0]==help[3]||
    help[1]==help[2]||help[1]==help[3]){
        return find (A,i,j+1,m,n,count);
    }
    else if(help[2]==help[3]){
        return find (A,i,j+2,m,n,count);
    }

    return find (A,i,j+1,m,n,count+1);
}

// 2 4
// 0 5 11 1 
// 11 5 0 5