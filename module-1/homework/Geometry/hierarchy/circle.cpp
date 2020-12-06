#include "circle.h"

Circle::Circle(Point center, double radius) : Ellipse(center, center, radius * 2) {}

double Circle::radius() const {
    return getA() / 2;
}

double Circle::perimeter() const {
    return 2 * PI * radius();
}

double Circle::area() const {
    return PI * radius() * radius();
}
