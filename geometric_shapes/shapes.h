#ifndef SHAPES_H
#define SHAPES_H
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

// структура для хранения координат точки
struct Point{
    double x, y;
};

// базовый абстрактный класс
class Shape {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual std::string name () = 0;
    virtual ~Shape() {}
};

// базовый класс для многоугольника 
class Polygon : public Shape {
protected:
    std::vector<Point> vertices; // список вершин многоугольника
public:
    Polygon(){}
    Polygon (const std::vector<Point>& v) : vertices(v) {}
    // конструктор читающий вершины из файла
    Polygon(std::string filename) {
        std::ifstream file(filename);
        if (file.is_open()){
            int count;
            file >> count; // считываем кол-во точек
            double x, y;
            while (file >> x >> y) { // читаем координаты
                vertices.push_back({x, y});
            }
        }
    }
    // расчет площади по формуле Гаусса
    double calc_area() override{
        if (vertices.size() < 3) return 0.0;
        double area = 0.0;
        int n = (int)vertices.size();
        for (int i = 0; i < n; i++) {
            Point p1 = vertices[i];
            Point p2 = vertices[(i + 1)% n];
            area += (p1.x * p2.y) - (p2.x * p1.y);
        }
        if (area < 0) area = -area;
        return area / 2.0;
    }
    
    // расчет периметра как суммы длин отрезков между вершинами
    double calc_perimetr() override {
        if (vertices.size() < 2) return 0.0;
        double p = 0.0;
        int n = (int)vertices.size();
        for (int i = 0; i < n; i++) {
            Point p1 = vertices[i];
            Point p2 = vertices[(i + 1)% n];
            double dx = p2.x - p1.x;
            double dy = p2.y - p1.y;

            p += std::sqrt(dx * dx + dy * dy);
        }
        return p;
    }
    std::string name() override{
        return "Polygon";
    }
};

class Rectangle : public Polygon {
public:
    using Polygon::Polygon;
    std::string name() override {
        return "Rectangle";
    }
};

class Triangle : public Polygon {
public:
    using Polygon::Polygon;
    std::string name() override { return "Triangle"; }
};

// ellipse and circle наследуются напрямую от shape, тк не имеют вершин
class Circle : public Shape {
    double radius;
    Point center;
public:
    Circle(Point c, double r) : center(c), radius(r) {}
    double calc_area() override {
        return 3.14 * radius * radius;
    }
    double calc_perimetr() override{
        return 2 * 3.14 * radius;
    }
    std::string name() override {
        return "Circle";
    }
};

class Ellipse : public Shape {
    double radiusA;
    double radiusB;
    Point center;
public:
    Ellipse(Point c, double a, double b) : center(c), radiusA(a), radiusB(b) {}
    double calc_area() override {
        return 3.14 * radiusA * radiusB;
    }
    double calc_perimetr() override {
        double a = radiusA;
        double b = radiusB;
        return 3.14 * (3 * (a + b) - std::sqrt((3 * a + b) * (a + 3 * b)));
    }
    std::string name() override {
        return "Ellipse";
    }
};

#endif 