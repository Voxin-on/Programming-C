#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;

    char* K=new char[n+1];
    cin.ignore();
    cin.getline(K,n+1);

    int help[256]={0};
    int shift=0;
    int i=0;

    for (i=0;*(K+i);i++){
        unsigned char c = (unsigned char)*(K+i);
        if (*(help+c)==0){
            *(K+i-shift)=c;
            (*(help+c))++;
        }
        else 
            shift++;
    }
    *(K+i-shift)='\0';

    cout<<K;

    delete[] K;

    return 0;
}