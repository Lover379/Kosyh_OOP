#pragma once
#include <string>
#include <vector>

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}
};

class Shape {
public:
    virtual ~Shape() {}
    virtual double calc_area() = 0;
    virtual double calc_perimeter() = 0;
    virtual std::string name() = 0;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r);
    double calc_area() override;
    double calc_perimeter() override;
    std::string name() override;
};

class Ellipse : public Shape {
private:
    double r1, r2;
public:
    Ellipse(double _r1, double _r2);
    double calc_area() override;
    double calc_perimeter() override;
    std::string name() override;
};

class Triangle : public Shape {
private:
    double side;
public:
    Triangle(double s);
    double calc_area() override;
    double calc_perimeter() override;
    std::string name() override;
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h);
    double calc_area() override;
    double calc_perimeter() override;
    std::string name() override;
};

class Polygon : public Shape {
private:
    std::vector<Point> vertices;
public:
    Polygon(const std::string& file_name);
    double calc_area() override;
    double calc_perimeter() override;
    std::string name() override;
};