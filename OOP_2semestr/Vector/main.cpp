#include "vector.h"
#include <iostream>

using namespace std;

int main(){
    cout<<"Assignment:"<<endl;
    Array a(1);
    Array b(5);
    for(int i=0;i<5;i++)b.insert(i);
    cout<<a.getSize()<<endl;
    a=b;
    cout<<a;
    
    cout<<"Change element by index:"<<endl;
    Array arr(5);
    for(int i=0;i<5;i++)arr.insert(i);

    cout<<arr[4]<<endl;
    arr[4]=20;
    cout<<arr[4]<<endl;

    cout<<"Insert:"<<endl;
    arr.insert(100);
    arr.insert(50,2);
    cout<<arr;

    cout<<"Copying:"<<endl;
    Array c(arr);
    cout<<c;

    cout<<"Remove element:"<<endl;
    b.remove(2);
    cout<<b;

    cout<<"Exception:"<<endl;
    try {
        b.remove(100);
    } 
    catch (const ArrayException& e) {
        cout<<"Error caught"<< endl;
    }

    return 0;
}