#include <iostream>
#include <locale.h>
using namespace std;
int main(){
    setlocale(LC_ALL, "Russian");
    int n;
    cin>>n;

    int* X=new int[n];
    for (int i=0;i<n;i++)cin>>X[i];
    int* Y=new int[n];
    for (int i=0;i<n;i++)cin>>Y[i];

    int k;
    cin>>k;

    if (k<=0 || k>n)return -1;

    bool flag;
    for (int i=0;i<=k-n;i++){
        flag=true;
        for (int j=0;j<k;j++){
            if (X[i+j]!=Y[j]){
                flag=false;
                break;
            }
        }
        if (flag){
            break;
        }

    }
    if (flag)cout<<"ДА";
    else cout<<"НЕТ";

    delete[] X;
    delete[] Y;

    return 0;
}
