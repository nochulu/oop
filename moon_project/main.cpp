#include <iostream>
#include <fstream>
#include <string>
#include "moon.h"
using namespace std;

int main() {
    int day, month, year;
    char dot1, dot2;

    cout << "Enter date (dd.mm.yyyy): ";
    if (!(cin >> day >> dot1 >> month >> dot2 >> year)) return 1;

    if (dot1 != '.' || dot2 != '.' || !isValid(year, month, day)) {
        cout << "Error: Invalid date!" << endl;
        return 1;
    }

    string filename = "Moon/Moon/moon" + to_string(year) + ".dat";
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: File " << filename << " not found!" << endl;
        return 1;
    }

    string header;
    getline(file, header); 

    string rise = "not found";
    string culmin = "not found";
    string set_time = "not found";

    double maxEl = -1000.0;
    double prevEl = -1000.0;
    bool dateFound = false;
    bool firstPointOfDate = true;

    long long targetYMD = (long long)year * 10000 + month * 100 + day;

    long long ymd;
    int hms;
    double t, r, el, az, fi, lg;

    while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg) {
        if (ymd == targetYMD) {
            dateFound = true;

            if (el > maxEl) {
                maxEl = el;
                culmin = formatTimeStr(hms);
            }

            if (!firstPointOfDate) {
                if (prevEl < 0 && el >= 0 && rise == "not found") {
                    rise = formatTimeStr(hms);
                }
                if (prevEl > 0 && el <= 0 && set_time == "not found") {
                    set_time = formatTimeStr(hms);
                }
            }

            prevEl = el;
            firstPointOfDate = false;
        } 
        else if (dateFound) {
            break;
        }
    }

    file.close();

    if (!dateFound) {
        cout << "No data for this date." << endl;
    } else {
        cout << "\nDate: " << day << "." << month << "." << year << endl;
        cout << "Moonrise:    " << rise << endl;
        cout << "Culmination: " << culmin << endl;
        cout << "Moonset:     " << set_time << endl;
    }

    cout << endl;
    system("pause");

    return 0;
}