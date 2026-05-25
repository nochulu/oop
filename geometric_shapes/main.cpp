#include "Shapes.h"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std; 

int main() {
    // вектор для хранения указателей на фигуры
    vector<Shape*> shapes;

    shapes.push_back(new Rectangle(vector<Point>{{0,0}, {10,0}, {10,5}, {0,5}}));
    shapes.push_back(new Circle(Point{5, 5}, 3.0));
    shapes.push_back(new Triangle(vector<Point>{{0,0}, {4,0}, {0,3}}));
    shapes.push_back(new Polygon("granitsy-uchastka2.txt"));
    
    int rectCount = 0, circleCount = 0, triCount = 0, noiseCount = 0;
    double totalArea = 0.0;

    cout << fixed << setprecision(2);
    // идем по списку и вызываем методы фигур
    for (Shape* s : shapes) {
        string name = s->name();
        totalArea += s->calc_area(); // суммируем площади

        if (name == "Rectangle") rectCount++;
        else if (name == "Circle") circleCount++;
        else if (name == "Triangle") triCount++;
        else noiseCount++; // все что не попало выше, просто шум

        cout << "Found: " << left << setw(12) << name 
             << " | Area: " << s->calc_area() << endl;
    }

    cout << "Rectangle = " << rectCount << endl;
    cout << "Circle    = " << circleCount << endl;
    cout << "Triangle  = " << triCount << endl;
    cout << "Noise     = " << noiseCount << endl;
    cout << "TOTAL AREA: " << totalArea << endl;

    for (Shape* s : shapes) {
        delete s;
    }
    shapes.clear();

    return 0;
}