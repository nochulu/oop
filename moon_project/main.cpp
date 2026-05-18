#include <iostream>
#include <fstream>
#include <string>
#include "moon.h"
using namespace std;

int main() {
    int day, month, year;
    char dot1, dot2;

    // просим ввести дату
    cout << "Enter date (dd.mm.yyyy): ";
    if (!(cin >> day >> dot1 >> month >> dot2 >> year)) return 1;

    // проверяем, что разделители — точки, и сама дата вообще существует
    if (dot1 != '.' || dot2 != '.' || !isValid(year, month, day)) {
        cout << "Error: Invalid date!" << endl;
        return 1;
    }

    // собираем путь к файлу нужного года
    string filename = "Moon/Moon/moon" + to_string(year) + ".dat";
    ifstream file(filename);

    // если файла с таким годом нет — выдаем ошибку
    if (!file.is_open()) {
        cout << "Error: File " << filename << " not found!" << endl;
        return 1;
    }

    // скипаем самую первую строчку в файле, там просто шапка таблицы
    string header;
    getline(file, header); 

    // значения, если ничего не найдем
    string rise = "not found";
    string culmin = "not found";
    string set_time = "not found";

    // технические переменные для поиска пика высоты и переходов через горизонт
    double maxEl = -1000.0;       
    double prevEl = -1000.0;      // сюда будем сохранять высоту из предыдущей строки
    bool dateFound = false;       // флаг, что дошли до нужной даты
    bool firstPointOfDate = true; // флаг для первой строчки за эти сутки

    // склеиваем дату в одно длинное число YYYYMMDD для удобного сравнения
    long long targetYMD = (long long)year * 10000 + month * 100 + day;

    // переменные, куда построчно выкачиваем данные из файла
    long long ymd; 
    int hms;       
    double t, r, el, az, fi, lg; 

    // побежали по строчкам файла
    while (file >> ymd >> hms >> t >> r >> el >> az >> fi >> lg) {
        // если наткнулись на нужный день
        if (ymd == targetYMD) {
            dateFound = true; 

            // ищем кульминацию: если текущая высота больше максимальной, обновляем рекорд
            if (el > maxEl) {
                maxEl = el;
                culmin = formatTimeStr(hms); // фиксируем время
            }

            // восход и заход считаем только со второй точки суток 
            if (!firstPointOfDate) {
                // если была под горизонтом (<0), а стала над (>=0) — это восход
                if (prevEl < 0 && el >= 0 && rise == "not found") {
                    rise = formatTimeStr(hms);
                }
                // если была над горизонтом (>0), а ушла под (<=0) — это заход
                if (prevEl > 0 && el <= 0 && set_time == "not found") {
                    set_time = formatTimeStr(hms);
                }
            }

            // обновление предыдущей высоту для следующего шага
            prevEl = el;
            firstPointOfDate = false;
        } 
        // если нужный день закончился и пошел уже следующий — стопаем цикл, чтоб не тратить время
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