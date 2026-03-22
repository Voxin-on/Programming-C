#include <iostream>
using namespace std;

bool Palindrom(char* world,int len);
int main(){
    char str[]="radar";
    if (Palindrom(str,5))
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;

     char str2[] = "yes";
    if (Palindrom(str2, 3)) 
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
bool Palindrom(char* world,int len){
    if (len<=1) 
        return true;
    else if (*world!=world[len-1])
        return false;
    else
        return Palindrom(world+1,len-2);
    
}