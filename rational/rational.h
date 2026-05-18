#include <iostream>

using namespace std;

class Rational {
private:
	int num; // числитель
	int dem; // знаменатель
	void simplify(); // функция сокращения дроби
public:
	Rational(); // дробь
	Rational(int number); // целое число как дробь
	Rational(int n, int d); // дробь с числ и знам

	Rational& operator =(const Rational& r);

	Rational& operator +=(const Rational& r);
	Rational& operator -=(const Rational& r);
	Rational& operator *=(const Rational& r);
	Rational& operator /=(const Rational& r);

	Rational operator +(const Rational& r) const;
	Rational operator -(const Rational& r) const;
	Rational operator *(const Rational& r) const;
	Rational operator /(const Rational& r) const;

	Rational operator -() const; // унарный минус


	Rational& operator ++(); 
	Rational operator ++(int);

	bool operator ==(const Rational& r) const;
	bool operator !=(const Rational& r) const;
	
	operator int() const; // округляет или отбрасывает
	operator double() const; // перевод в десятичное число

	friend istream& operator >>(istream& in, Rational& r);
	friend ostream& operator <<(ostream& out, const Rational& r);

};