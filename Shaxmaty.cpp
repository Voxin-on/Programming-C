#include <iostream>
#include <fstream>
#include <locale.h>
using namespace std;

bool readQueens(const char *fileName, int *qx, int *qy);
bool isThreaten(int qx1, int qy1, int qx2, int qy2);
void writePair(ofstream &out, int qx1, int qy1, int qx2, int qy2);
int readVert(ifstream &in);
int readHoris(ifstream &in);
bool check(int qx1, int qy1, int qx2, int qy2,int* qx, int* qy);

int main()
{
    setlocale(LC_ALL, "Russian");
    int qx[8], qy[8];
    if (!readQueens("in.txt", qx, qy))
    {
        cout << "Не удалось прочитать координаты" << endl;
        return -1;
    }
    ofstream out("out.txt");
    if (!out.is_open())
    {
        cout << "Не удалось создать выходной файл" << endl;
        return -2;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = i + 1; j < 8; j++)
        {
            if (isThreaten(qx[i], qy[i], qx[j], qy[j]) &&
            check(qx[i], qy[i], qx[j], qy[j], qx, qy))
                writePair(out, qx[i], qy[i], qx[j], qy[j]);
        }
    }
    return 0;
}

bool readQueens(const char *fileName, int *qx, int *qy)
{
    ifstream in(fileName);
    if (!in.is_open())
        return false;
    for (int i = 0; i < 8; i++)
    {
        qx[i] = readVert(in);
        qy[i] = readHoris(in);
        if (in.fail() || qx[i] == 0 || qy[i] == 0)
            return false;
    }
    return true;
}

int readVert(ifstream &in)
{
    char ch;
    in >> ch;
    if (ch < 'a' || ch > 'h')
        return 0;
    return ch - 'a' + 1;
}
int readHoris(ifstream &in)
{
    char ch;
    in >> ch;
    if (ch < '1' || ch > '8')
        return 0;
    return ch - '1' + 1;
}

bool isThreaten(int qx1, int qy1, int qx2, int qy2)
{
    return (qx1 == qx2) || (qy1 == qy2) || (qx1 - qx2 == qy1 - qy2) || (qx2 - qx1 == qy1 - qy2);
}

void writePair(ofstream &out, int qx1, int qy1, int qx2, int qy2)
{
    char qv1 = (qx1 - 1) + 'a';
    char qv2 = (qx2 - 1) + 'a';
    out << qv1 << qy1 << '-' << qv2 << qy2 << endl;
}

bool check(int qx1, int qy1, int qx2, int qy2,int* qx, int* qy){
    for(int i = 0; i < 8; i++){
        if((qx[i] == qx1 && qy[i] == qy1) || (qx[i] == qx2 && qy[i] == qy2))
            continue;
        if (
            qx1 == qx2 && qx[i] == qx1 &&
            (qy[i] > qy1 && qy[i] < qy2 || qy[i] > qy2 && qy[i] < qy1)
            ||

            qy1 == qy2 && qy[i] == qy1 &&
            (qx[i] > qx1 && qx[i] < qx2 || qx[i] > qx2 && qx[i] < qx1)
            ||

            (qx1 - qx[i] == qy1 - qy[i] || qx1 - qx[i] == qy[i] - qy1)
            &&
            (qx2 - qx[i] == qy2 - qy[i] || qx2 - qx[i] == qy[i] - qy2)
            &&
            (qy[i] > qy1 && qy[i] < qy2 || qy[i] > qy2 && qy[i] < qy1)
            &&
            (qx[i] > qx1 && qx[i] < qx2 || qx[i] > qx2 && qx[i] < qx1)
        ) 
            return false;
    }
    return true;
}