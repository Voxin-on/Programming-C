#include "rational.h"
#include <iostream>
#include <cmath>


void Rational::simplify()
{
    if (denom!=0){
        if (denom < 0) {
            numer = -numer;
            denom = -denom;
        }

        int a = abs(numer);
        int b = denom;

        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }

        numer /= a;
        denom /= a;
    }
}



Rational::Rational()
{
 numer=0;
 denom=1;
}

Rational::Rational(int number)
{
    numer=number;
    denom=1;
}

Rational::Rational(int n, int d)
{
    numer=n;
    denom=d;
}

Rational::Rational(double number){
    denom = 1000000;
    numer = number * denom + (number >= 0 ? 0.5 : -0.5);
    simplify();
}



Rational& Rational::operator +=(const Rational& r)
{
    numer = (numer*r.denom+denom*r.numer);
    denom *= r.denom;
    simplify();
    return *this;
}

Rational Rational::operator +(const Rational &r) const
{
    Rational res(*this);
    return res += r;
}

Rational& Rational::operator -=(const Rational& r)
{
    return (*this += (-r));
}

Rational Rational::operator -(const Rational& r) const
{
    Rational res(*this);
    return res -= r;
}

Rational& Rational::operator *=(const Rational& r)
{
    numer *=r.numer;
    denom *= r.denom;
    simplify();
    return *this;
}

Rational Rational::operator *(const Rational &r) const
{
    Rational res(*this);
    return res *= r;
}

Rational& Rational::operator /=(const Rational& r)
{
    Rational rev(r.denom,r.numer);
    return *this *= rev;
}

Rational Rational::operator /(const Rational &r) const
{
    Rational res(*this);
    return res /= r;
}

Rational& Rational::operator ++()
{
    numer += denom;
    return *this;
}

Rational Rational::operator ++(int)
{
    Rational r(*this);
    numer += denom;
    return r;
}

Rational& Rational::operator --()
{
    numer -= denom;
    simplify();
    return *this;
}

Rational Rational::operator --(int)
{
    Rational r(*this);
    numer -= denom;
    simplify();
    return r;
}

Rational Rational::operator -() const
{
    Rational r(-numer, denom);
    return r;
}



bool Rational::operator ==(const Rational& r) const
{
    return (numer==r.numer) && (denom==r.denom);
}

bool Rational::operator !=(const Rational& r) const
{
    return !(*this==r);
}

bool Rational::operator<(const Rational& r) const 
{
    return numer * r.denom < r.numer * denom;
}

bool Rational::operator<=(const Rational& r) const 
{
    return *this < r || *this == r;
}

bool Rational::operator>(const Rational& r) const 
{
    return !(*this <= r);
}

bool Rational::operator>=(const Rational& r) const 
{
    return !(*this < r);
}



Rational::operator int() const
{
    return numer / denom;
}
Rational::operator double() const
{
    return ((double)numer)/denom;
}



istream& operator >>(istream& in, Rational& r)
{
    in>>r.numer>>r.denom;
    return in;
}
ostream& operator <<(ostream& out, const Rational& r)
{
    out<<r.numer<<"/"<<r.denom;
    return out;
}



void solveQuadratic(const Rational& a, const Rational& b, const Rational& c)
{
    if (a == Rational(0)) {
        if (b == Rational(0)) {
            if (c == Rational(0))
                cout << "Бесконечно много решений" << endl;
            else
                cout << "Нет решений" << endl;
        }
        else {
            Rational x = -c / b;
            cout << "Линейное уравнение, x = " << x << endl;
        }
        return;
    }
    Rational d = b*b - Rational(4)*a*c;

    if (d < Rational(0)) {
        cout << "Нет корней"<<endl;
        return;
    }

    Rational neg_b = -b;
    Rational two_a = Rational(2) * a;

    if (d == Rational(0)) {
        cout << "x = " << neg_b / two_a << endl;
        return;
    }

    int sq_num = (int)round(sqrt((double)d.numer));
    int sq_den = (int)round(sqrt((double)d.denom));

    if (sq_num * sq_num == d.numer && sq_den * sq_den == d.denom){
        Rational sqrt_d(sq_num, sq_den);

        Rational x1 = (neg_b + sqrt_d) / two_a;
        Rational x2 = (neg_b - sqrt_d) / two_a;

        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
    else {
        double sqrtD = sqrt((double)d);

        double x1 = (double(neg_b) + sqrtD) / double(two_a);
        double x2 = (double(neg_b) - sqrtD) / double(two_a);

        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
}