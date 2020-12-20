#include <vector>
#include "polygon.h"
#include "triangle.h"

Triangle::Triangle(Point const &p1, Point const &p2, Point const &p3) : Polygon({p1, p2, p3}) {}

Circle Triangle::circumscribedCircle() const {
    auto points = getVertices();
    Point p1 = points[0], p2 = points[1], p3 = points[2];
    Line m1{(p1 + p2) / 2, p3};
    Line m2{(p1 + p3) / 2, p2};
    Point center = m1.intersect(m2);
    double radius = (p3 - p2).abs() * (p2 - p1).abs() * (p1 - p3).abs() / (4 * area());
    return {center, radius};
}

Circle Triangle::inscribedCircle() const {
    auto points = getVertices();
    Point p1 = points[0], p2 = points[1], p3 = points[2];
    Line b1{p3 + (p1 - p3).normalized() + (p2 - p3).normalized(), p3};
    Line b2{p2 + (p1 - p2).normalized() + (p3 - p2).normalized(), p2};
    Point center = b1.intersect(b2);
    double radius = 2 * area() / perimeter();
    return {center, radius};
}
