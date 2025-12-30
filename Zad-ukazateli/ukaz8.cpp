#include <iostream>
using namespace std;

void InsertionSort(int* arr,int size);

int main(){
    int m,n;
    cin>>m>>n;

    int** L=new int*[m];
    for (int i=0;i<m;i++){
        L[i]=new int[n];
        for (int j=0;j<n;j++)
            cin>>L[i][j];
    }

    int* help=new int[m];

    for(int i=0;i<m;i++){
        int val=0;
        for (int j=0;j<n;j++)
            val=val*2+*(*(L+i)+j);
        *(help+i)=val;
    }
    
    InsertionSort(help,m);

    int newM = 1;
    for (int i = 1; i < m; i++)
        if (*(help+i) != *(help+i-1))
            *(help+newM++) = *(help+i);

    for (int i=0;i<newM;i++){
        int val=*(help+i);
        for (int j=n-1;j>=0;n--){
            *(*(L+i)+j)=val&1;
            val>>1;
        }
    }

    for(int i=0;i<newM;i++)
        for (int j=0;j<n;j++) 
            cout<<*(*(L+i)+j);

    for (int i=0;i<m;i++) delete L[i];
    delete[] L;

    return 0;
}

void InsertionSort(int* arr,int size){
    int buf;
    int i,j;
    for (int i=1;i<size;i++){
        buf=arr[i];
        for (int j=i-1;j>=0&&buf<arr[j];j--)
            arr[j+1]=arr[j];
        arr[j+1]=buf;
    }
}