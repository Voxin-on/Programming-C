#include <iostream>
#include "rational.h"
#include <locale.h>
#include <cmath>

using namespace std;

void solveQuadratic(const Rational& a, const Rational& b, const Rational& c) {
    if (a == Rational(0)) {
        if (b == Rational(0)) {
            cout << (c == Rational(0) ? "Бесконечно много решений" : "Нет решений") << endl;
        } else {
            cout << "Линейное уравнение, x = " << -c / b << endl;
        }
        return;
    }

    Rational d = b * b - Rational(4) * a * c;

    if (d < Rational(0)) {
        cout << "Нет корней" << endl;
        return;
    }

    Rational neg_b = -b;
    Rational two_a = Rational(2) * a;

    if (d == Rational(0)) {
        cout << "x = " << neg_b / two_a << endl;
    } else {
        Rational sqrt_d(sqrt((double)d));
        cout << "x1 = " << (neg_b + sqrt_d) / two_a << endl;
        cout << "x2 = " << (neg_b - sqrt_d) / two_a << endl;
    }
}

int main(){
    setlocale(LC_ALL, "Russian");

    Rational a(1,2), b(1,2), c(2,3);
    cout<<"Compare"<< endl;

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

    cout<<-a<< endl;

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

    Rational t1(0);
    try{
        solveQuadratic(t1, Rational(0), Rational(0)); // все 0 бесконечно много
        solveQuadratic(t1, Rational(0), Rational(1)); // 1!=0 нету решений
        solveQuadratic(t1, Rational(1), Rational(1)); // линейное -1

        Rational t2(1);
        solveQuadratic(t2, Rational(0), Rational(1)); // d<0 нету корней 
        solveQuadratic(t2, Rational(-4), Rational(4)); // 16-16 d=0 x = 2  
        solveQuadratic(t2, Rational(-5), Rational(6)); // d=1 x=3 x=2
        solveQuadratic(t2, Rational(0), Rational(-2)); // d=8 x=корень(2) x=-корень(2)

        cout<<"Exception(limit)"<<endl;
        Rational l1(0x7FFFFFFF);
        Rational l2(0x7FFFFFFF);
        l1+=l2;
    }
    catch(const RationalException& e){
        cout<<"Limit exception"<<endl;
    }
    
    return 0;
}