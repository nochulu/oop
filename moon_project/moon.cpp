#include "moon.h"

bool isValid(int y, int m, int d) {
    if (y < 1900 || y > 2100 || m < 1 || m > 12 || d < 1) return false;
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) {
        days[2] = 29;
    }
    return d <= days[m];
}

std::string formatTimeStr(int hms) {
    int hh = hms / 10000;
    int mm = (hms % 10000) / 100;
    int ss = hms % 100;
    
    std::string res = "";
    if (hh < 10) res += "0"; res += std::to_string(hh) + ":";
    if (mm < 10) res += "0"; res += std::to_string(mm) + ":";
    if (ss < 10) res += "0"; res += std::to_string(ss);
    
    return res;
}