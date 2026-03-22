#include <iostream>
#include <locale.h>
using namespace std;

int main()
{
    setlocale(LC_ALL,"Russian");
    char arr[81];
    cin.getline(arr, 80, '\n');
    
    char help[81];
    char* phelp=help;
    int maxLen[81];
    int* pmaxLen=maxLen;
    int cur=0;
    bool after=false;

    for (int i = 0; *(arr+i) != '\0'; i++) {
        if (*(arr+i) == '('){ 
            if (after)after=false;
            *(phelp++) = *(arr+i);
            cur++;
        }
        else if (*(arr+i) == ')') {
            if (!after){
                after=true;
                *(pmaxLen++)=cur;
                cur=0;
            }
            if (phelp == help||*(--phelp) != '(') { cout << "Некорректно"; return 0; }
        }
    }
    cout << (phelp==help ? "Корректно" : "Некорректно")<<endl;

    pmaxLen=maxLen;
    after=false;
    for (int i = 0; *(arr+i) != '\0'; i++) {
        if (*(arr+i) == '(') {
            if (after){
                pmaxLen++;
                after=false;
            }
            cur++;
            int level=*(pmaxLen)-cur;
            if (level==0) continue;
            else if (level==1) *(arr+i) ='[';
            else *(arr+i) ='{';
        }
        else if (*(arr+i) == ')') {
            if (!after)after=true;
            int level=*(pmaxLen)-cur;
            cur--;
            if (level==0) continue;
            else if (level==1) *(arr+i) =']';
            else *(arr+i) ='}';
        }
    }
    
    cout<<arr;

    return 0;
}