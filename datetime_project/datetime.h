#include <iostream>
#include <string>

class DateTime {
private:
    int year, month, day;
    int h, m, s;

public:
    DateTime();
    DateTime(int y, int mon, int d, int hr = 0, int min = 0, int sec = 0);

    int operator-(const DateTime& other) const;
    DateTime operator+(int days) const;
    DateTime operator-(int days) const;

    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;

    bool isValid() const;
    std::string getDayOfWeek() const;
    void printFormatted(int style) const;

    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
    friend std::istream& operator>>(std::istream& is, DateTime& dt);
};