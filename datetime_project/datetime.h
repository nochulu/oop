#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>

class DateTime {
private:
    int year, month, day;
    int h, m, s;

public:
    // Конструкторы
    DateTime();
    DateTime(int y, int mon, int d, int hr = 0, int min = 0, int sec = 0);

    // Проверка корректности и утилиты
    bool isValid() const;
    std::string getDayOfWeek() const;
    void printFormatted(int style) const;

    // Арифметика дат (все эти операторы ОБЯЗАНЫ быть тут)
    int operator-(const DateTime& other) const; // Разность двух дат в днях (int)
    DateTime operator+(int days) const;         // Прибавление дней к дате
    DateTime operator-(int days) const;         // Вычитание дней из даты

    // Операторы сравнения
    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;

    // Дружественные функции для ввода/вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
    friend std::istream& operator>>(std::istream& is, DateTime& dt);
};

#endif // DATETIME_H