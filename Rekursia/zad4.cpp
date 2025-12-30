#include <iostream>
using namespace std;

int divs(int N,int del=2);
int main(){
    cout<<divs(5)<<' '<<divs(18);
    return 0;
}

int divs(int N,int del){
    if (del>=N)
        return 0;
    else if (N%del==0)
        return 1+divs(N,del+1);
    else
        return divs(N,del+1);
}