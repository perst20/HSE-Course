#include "rectangle.h"

Rectangle::Rectangle(const Point &p1, const Point &p2, double e) {
    Point p3{};
    p3.x = (-p1.y * e + p2.y * e + e * e * p2.x + p1.x) / (e * e + 1.0);
    p3.y = (p1.y + e * (p2.y * e + p1.x - p2.x)) / (e * e + 1.0);
    vertices_ = {p1, p3, p2, p2 + (p1 - p3)};
}

Point Rectangle::center() const {
    return (vertices_[0] + vertices_[2]) / 2;
}
