#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
using namespace std;

class RationalException {};

class Rational
{
    private:
        void simplify();

    public:
        int numer;
        int denom;
    
        Rational();
        Rational(int number);
        Rational(int n, int d);
        Rational(double number);

        Rational& operator +=(const Rational& r);
        Rational operator +(const Rational& r) const;

        Rational& operator -=(const Rational& r);
        Rational operator -(const Rational& r) const;

        Rational& operator *=(const Rational& r);
        Rational operator *(const Rational& r) const;

        Rational& operator /=(const Rational& r);
        Rational operator /(const Rational& r) const;

        Rational& operator ++();
        Rational operator ++(int);

        Rational& operator --();
        Rational operator --(int);

        Rational operator -() const;

        bool operator ==(const Rational& r) const;
        bool operator !=(const Rational& r) const;
        bool operator<(const Rational& r) const;
        bool operator<=(const Rational& r) const;
        bool operator>(const Rational& r) const;
        bool operator>=(const Rational& r) const;

        operator int() const;
        operator double() const;

        friend istream& operator >>(istream& in, Rational& r);
        friend ostream& operator <<(ostream& out, const Rational& r);


};

void solveQuadratic(const Rational& a, const Rational& b, const Rational& c);

#endif