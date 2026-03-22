#include <iostream>
using namespace std;

bool equal(int N,int S);
int main(){
    cout<<equal(12345,15);
    return 0;
}

bool equal(int N,int S){
    if (N==0){
        return S==0;
    }
    return equal(N/10,S-(N%10));
}