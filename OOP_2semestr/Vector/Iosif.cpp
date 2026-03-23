#include "vector.h"
#include <iostream>
#include <ctime>

using namespace std;

int main(){
    int numbers[7]={1000,5000,10000,50000,100000,500000,1000000};

    for (int i=0;i<7;i++){
        
        int N=numbers[i];
        int k=2;

        Array arr(N);

        clock_t start = clock();

        for (int j=0;j<N;j++){
            arr.insert(j);
        }

        int ind=0;
        while(arr.getSize()>1){
            ind=(ind+k-1)%arr.getSize();

            arr.remove(ind);
        }

        double time = (double)(clock() - start) / CLOCKS_PER_SEC;

        cout<<"N: "<<N<<" Answer: "<<arr[0]+1<<" Time: "<<time<<endl;
    }

    return 0;
}