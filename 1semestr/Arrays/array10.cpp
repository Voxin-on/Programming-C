#include <iostream>
using namespace std;

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

    cout<<"Before:"<<endl;
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            cout<<A[i][j]<<' ';
        }
        cout<<endl;
    }

    int* col=new int[n];
    int indCol=0;
    bool flag=false;
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            if (A[i][j]==0){
                flag=true;
                col[indCol++]=j;
            }
            }
        if (flag){
            for (int j=0;j<n;j++){
                A[i][j]=0;
            }
        }
        flag=false;
    }

    for (int i=0;i<m;i++){
        for (int j=0;j<indCol;j++){
            A[i][col[j]]=0;
        }
    }

    cout<<"After:"<<endl;
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            cout<<A[i][j]<<' ';
        }
        cout<<endl;
    }

    for (int i=0;i<m;i++)delete[] A[i];
    delete[] A;
    delete[] col;

    return 0;
}