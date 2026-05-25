#include "figures.h"
#include <fstream>
#include <sstream>
#include <cmath>

Circle::Circle(double r) : radius(r) {}
double Circle::calc_area() { return 3.141592653589793 * radius * radius; }
double Circle::calc_perimeter() { return 2 * 3.141592653589793 * radius; }
std::string Circle::name() { return "Circle"; }

Ellipse::Ellipse(double _r1, double _r2) : r1(_r1), r2(_r2) {}
double Ellipse::calc_area() { return 3.141592653589793 * r1 * r2; }
double Ellipse::calc_perimeter() { return 3.141592653589793 * (3 * (r1 + r2) - std::sqrt((3 * r1 + r2) * (r1 + 3 * r2))); }
std::string Ellipse::name() { return "Ellipse"; }

Triangle::Triangle(double s) : side(s) {}
double Triangle::calc_area() { return (std::sqrt(3.0) / 4.0) * side * side; }
double Triangle::calc_perimeter() { return 3.0 * side; }
std::string Triangle::name() { return "Triangle"; }

Rectangle::Rectangle(double w, double h) : width(w), height(h) {}
double Rectangle::calc_area() { return width * height; }
double Rectangle::calc_perimeter() { return 2.0 * (width + height); }
std::string Rectangle::name() { return "Rectangle"; }

Polygon::Polygon(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        double x, y;
        if (ss >> x >> y) {
            vertices.push_back(Point(x, y));
        }
    }
    file.close();
}
double Polygon::calc_area() {
    double area = 0.0;
    int n = static_cast<int>(vertices.size());
    if (n < 3) return 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}
double Polygon::calc_perimeter() {
    double perimeter = 0.0;
    int n = static_cast<int>(vertices.size());
    if (n < 2) return 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        perimeter += std::hypot(vertices[j].x - vertices[i].x, vertices[j].y - vertices[i].y);
    }
    return perimeter;
}
std::string Polygon::name() { return "Polygon"; }