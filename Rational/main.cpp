#include <iostream>
#include "rational.h"
#include <locale.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "Russian");

    solveQuadratic(Rational(1), Rational(-5), Rational(6));
    solveQuadratic(Rational(1), Rational(-4), Rational(4));
    solveQuadratic(Rational(1), Rational(0), Rational(-2));

    Rational a(1,2), b(-1,6);
    cout<<"a="<<a<<" b="<<b<<" a+b="<<a+b<<endl;
    cout<<"a("<<a<<") *= b("<<b<<")"<<endl;
    a *= b;
    cout<<"a="<<a<<" b="<<b<<" a-b="<<a-b<<endl;
    Rational c=3;
    cout<<"b="<<b<<" c="<<c<<" b/c="<<b/c<<endl;

    Rational e(7,8), f(5,12);
    cout<<"e="<<e<<" f="<<f<<" e+f=?"<<endl;
    cout<<"Введите результат g=m/n в формате: m n"<<endl;
    Rational g;
    cin>>g;
    if (e+f!=g)
        cout<<"Неправильно! e+f="<<e+f<<endl;
    else
        cout<<"Правильно!"<<endl;

    return 0;
}