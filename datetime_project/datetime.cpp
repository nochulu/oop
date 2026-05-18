#include "datetime.h"

using namespace std;

DateTime::DateTime() : year(2000), month(1), day(1), h(0), m(0), s(0) {}

DateTime::DateTime(int y, int mon, int d, int hr, int min, int sec) 
    : year(y), month(mon), day(d), h(hr), m(min), s(sec) {}

bool isLeapYear(int y) { //функция проверки, является ли год високосным
    // год високосный, если он делится на 4 и не делится на 100, либо делится на 400
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); 
}

int daysInMon(int mon, int y) { // функция возвращает количество дней в конкретном месяце конкретного года
    int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; 
    if (mon == 2 && isLeapYear(y)) return 29; // если февраль и год високосный, то в месяце 29 дней
    return days[mon];
}

// проверка даты и времени на корректность
bool DateTime::isValid() const {
    // проверка базовых диапазонов для года, месяца и дня
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;
    // проверка, что день не превышает максимально допустимый в этом месяце
    if (day > daysInMon(month, year)) return false;
    // проверка диапазонов для часов, минут и секунд
    if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59) return false;
    return true;
}

//алгоритм Юлианского дня
long long totalDays(int y, int mon, int d) {
    int a = (14 - mon) / 12;
    int yy = y + 4800 - a;
    int mm = mon + 12 * a - 3;
    // формула перевода даты в последовательное число дней
    return d + (153 * mm + 2) / 5 + 365LL * yy + yy / 4 - yy / 100 + yy / 400 - 32045;
}

// определение дня недели
string DateTime::getDayOfWeek() const {
    long long d = totalDays(year, month, day);
    string weeks[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    return weeks[(d + 1) % 7];
}

void DateTime::printFormatted(int style) const {
    string months[] = { "", "January", "February", "March", "April", "May", "June", 
                        "July", "August", "September", "October", "November", "December" };
    if (style == 1) { // 1.01.2001
        cout << day << "." << (month < 10 ? "0" : "") << month << "." << year;
    } else if (style == 2) { // 1 January 2001
        cout << day << " " << months[month] << " " << year;
    } else if (style == 3) { // 01.01.01
        if (day < 10) cout << '0'; cout << day << ".";
        if (month < 10) cout << '0'; cout << month << ".";
        int sy = year % 100; // получаем две последние цифры года
        if (sy < 10) cout << '0'; cout << sy;
    }
    cout << endl;
}

// оператор вычитания двух дат (возвращает разницу в днях между ними)
int DateTime::operator-(const DateTime& other) const {
    return (int)(totalDays(year, month, day) - totalDays(other.year, other.month, other.day));
}

// оператор сложения (добавляет к текущей дате заданное количество дней)
DateTime DateTime::operator+(int days) const {
    DateTime res = *this;
    res.day += days;
    // перемотка вперед, если дней стало больше, чем вмещает текущий месяц
    while (res.day > daysInMon(res.month, res.year)) {
        res.day -= daysInMon(res.month, res.year);
        if (++res.month > 12) { res.month = 1; res.year++; }
    }
    // перемотка назад, если прибавили отрицательное число дней и вышли за рамки месяца
    while (res.day < 1) {
        if (--res.month < 1) { res.month = 12; res.year--; }
        res.day += daysInMon(res.month, res.year);
    }
    return res;
}

DateTime DateTime::operator-(int days) const { return *this + (-days); }
bool DateTime::operator>(const DateTime& other) const  { return (*this - other) > 0; }
bool DateTime::operator>=(const DateTime& other) const { return (*this - other) >= 0; }
bool DateTime::operator<(const DateTime& other) const  { return (*this - other) < 0; }
bool DateTime::operator<=(const DateTime& other) const { return (*this - other) <= 0; }
bool DateTime::operator==(const DateTime& other) const { return (*this - other) == 0; }
bool DateTime::operator!=(const DateTime& other) const { return !(*this == other); }

ostream& operator<<(ostream& os, const DateTime& dt) {
    os << dt.year << "-";
    if (dt.month < 10) os << '0'; os << dt.month << "-";
    if (dt.day < 10) os << '0'; os << dt.day << "T";
    if (dt.h < 10) os << '0'; os << dt.h << ":";
    if (dt.m < 10) os << '0'; os << dt.m << ":";
    if (dt.s < 10) os << '0'; os << dt.s;
    return os;
}

istream& operator>>(istream& is, DateTime& dt) {
    char s;
    is >> dt.year >> s >> dt.month >> s >> dt.day >> s >> dt.h >> s >> dt.m >> s >> dt.s;
    return is;
}