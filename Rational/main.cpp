#include <iostream>
#include "rational.h"
#include <locale.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "Russian");

    Rational a(1,2), b(1,2), c(2,3);
    cout<<"Compare"<< endl;;

    cout<<(a==b)<< endl;
    cout<<(a!=c)<< endl;
    cout<<(a<c)<< endl;
    cout<<(a<b)<< endl;
    cout<<(a<=b)<< endl;
    cout<<(c>a)<< endl;
    cout<<(a>b)<< endl;
    cout<<(a>=b)<< endl;

    cout<<"Arithmetic"<< endl;

    cout<<a+b<< endl;
    cout<<a-b<< endl;
    cout<<a*b<< endl;
    cout<<a/b<< endl;

    cout<<(c+=b)<< endl;
    cout<<(c-=b)<< endl;
    cout<<(c*=b)<< endl;
    cout<<(c/=b)<< endl;

    cout<<a++<< endl;
    cout<<a<< endl;
    cout<<++a<< endl;

    cout<<a--<< endl;
    cout<<a<< endl;
    cout<<--a<< endl;

    cout<<-a<< endl;;

    cout<<"Type switch"<<endl;
    cout<<(int)a<< endl;
    cout<<(double)a<< endl;

    cout<<"Constructors"<<endl;
    Rational a1;
    cout<<a1<<endl;
    Rational a2(5);
    cout<<a2<<endl;
    Rational a3(5,10);
    cout<<a3<<endl;
    Rational a4(0.25);
    cout<<a4<<endl;

    cout<<"Quadratics"<<endl;

    solveQuadratic(Rational(0), Rational(0), Rational(0));
    solveQuadratic(Rational(0), Rational(0), Rational(1));
    solveQuadratic(Rational(0), Rational(1), Rational(1));

    solveQuadratic(Rational(1), Rational(0), Rational(1));
    solveQuadratic(Rational(1), Rational(-4), Rational(4));
    solveQuadratic(Rational(1), Rational(-5), Rational(6));
    solveQuadratic(Rational(1), Rational(0), Rational(-2));

    return 0;
}