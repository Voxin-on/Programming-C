
#include <iostream>
#include <locale.h>
using namespace std;

void toMorze(char* text, char* resultToMorze, int size);
void toBack(char* morze, char* resultToBack, int size);

const char* morzeCodes[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

int main()
{
    setlocale(LC_ALL,"Russian");
    int n;
    cin>> n;

    char* text=new char[n+1];
    char* resultToMorze=new char[n*5+1];
    char* resultToBack=new char[n+1];
    cin.ignore();
    cin.getline(text, n+1);
    toMorze(text,resultToMorze,n*5+1);

    cout << text<<" перевод в морзу: "<< resultToMorze<<endl;
    toBack(resultToMorze, resultToBack, n+1);
    cout<<resultToMorze<<" перевод обратно: "<<resultToBack;
    
    delete[] text;
    delete[] resultToMorze;
    delete[] resultToBack;
    return 0;
}

void toMorze(char* text,char* resultToMorze,int size) {
    int j = 0;
    for (int i = 0; text[i] != '\0' && j < size - 1; i++) {
        if (text[i]==' ') {
            resultToMorze[j++] = ' ';
            resultToMorze[j++] = ' ';
            resultToMorze[j++] = ' ';
        }

        else if (text[i] >= 'A' && text[i] <= 'Z') {
            const char* code= morzeCodes[text[i] - 'A'];

            for (int k = 0; code[k] != '\0'; k++)
                resultToMorze[j++] = code[k];
        }

        else if (text[i] >= 'a' && text[i] <= 'z') {
            const char* code = morzeCodes[text[i] - 'a'];

            for (int k = 0; code[k] != '\0' && j < size - 1; k++)
                resultToMorze[j++] = code[k];
        }

        if (text[i + 1] != '\0' && text[i + 1] != ' ' && j < size - 1)
            resultToMorze[j++] = ' ';
    }
    resultToMorze[j] = '\0';
}

void toBack(char* morze, char* resultToBack, int size) {
    int j = 0;
    for (int i = 0; morze[i] != '\0'; i++) {
        if (morze[i] == ' ' && morze[i + 1] == ' ' && morze[i + 2] == ' ') {
            resultToBack[j++] = ' ';
            i += 2;
        }

        else if (morze[i] == ' ')
            continue;

        else {
            char c[5];
            int forChar = 0;
            while (morze[i]!=' '&&morze[i] != '\0') 
                c[forChar++] = morze[i++];

            c[forChar]='\0';
            i--;
            for (int k=0;k<26;k++){
                const char* code= morzeCodes[k];
                bool flag=true;
                for (int o=0;code[o]!='\0'||c[o]!='\0';o++){
                    if (code[o]!=c[o]){
                        flag=false;
                        break;
                    }
                }
                if (flag){
                    resultToBack[j++]='A'+k;
                    break;
                }
            }
        }
    }
    resultToBack[j]='\0';
}