#include <iostream>
#include "rational.h"

using namespace std;

int main() {
    Rational a(1, 2);
    Rational b(-1, 6);
    Rational c(3);
    Rational d; 

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;

    Rational x(1, 2);
    Rational y(1, 3);

    x += y;
    cout << "x += y -> " << x << endl;

    x -= y;
    cout << "x -= y -> " << x << endl;

    x *= y;
    cout << "x *= y -> " << x << endl;

    x /= y;
    cout << "x /= y -> " << x << endl;

}