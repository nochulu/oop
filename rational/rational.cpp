#include <iostream>
#include "rational.h"
#include <cstdlib>  
using namespace std;

Rational::Rational() {
    num = 0;
    dem = 1; // чтобы на ноль не делить
}

Rational::Rational(int number) {
    num = number;
    dem = 1;
}

Rational::Rational(int n, int d) {
    num = n;
    dem = d;
    simplify();  
}

Rational& Rational::operator=(const Rational& r) {
    num = r.num;
    dem = r.dem;
    return *this;
}

void Rational::simplify() {
    // если минус оказался в знаменателе, перекидываем его наверх
    if (dem < 0) {
        num = -num;
        dem = -dem;
    }

    // ищем общие делители для числителя и знаменателя
    for (int i = 2; i <= abs(dem) && i <= abs(num); i++) {
        if (num % i == 0 && dem % i == 0) {
            num /= i;
            dem /= i;
            i--;
        }
    }
}

Rational& Rational::operator+=(const Rational& r) {
    num = num * r.dem + dem * r.num;
    dem = dem * r.dem;
    simplify();
    return *this;
}

Rational& Rational::operator-=(const Rational& r) {
    return (*this += (-r));
}

Rational& Rational::operator*=(const Rational& r) {
    num = num * r.num;
    dem = dem * r.dem;
    simplify();
    return *this;
}

Rational& Rational::operator/=(const Rational& r) {
    num = num * r.dem;
    dem = dem * r.num;
    simplify();
    return *this;
}

Rational Rational::operator+(const Rational& r) const {
    Rational res(*this);
    return res += r;
}

Rational Rational::operator-(const Rational& r) const {
    Rational res(*this);
    return res -= r;
}

Rational Rational::operator*(const Rational& r) const {
    Rational res(*this);
    return res *= r;
}

Rational Rational::operator/(const Rational& r) const {
    Rational res(*this);
    return res /= r;
}

Rational Rational::operator-() const {
    Rational r(-num, dem);
    return r;
}

Rational& Rational::operator++() {
    num += dem;
    return *this;
}

Rational Rational::operator++(int) {
    Rational r(*this);
    num += dem;
    return r;
}

bool Rational::operator==(const Rational& r) const {
    return (num == r.num) && (dem == r.dem);
}

bool Rational::operator!=(const Rational& r) const {
    return !(*this == r);
}

Rational::operator int() const {
    return num / dem;
}

Rational::operator double() const {
    return ((double)num) / dem;
}

istream& operator>>(istream& in, Rational& r) {
    in >> r.num >> r.dem;
    r.simplify();
    return in;
}

ostream& operator<<(ostream& out, const Rational& r) {
    out << r.num << "/" << r.dem;
    return out;
}