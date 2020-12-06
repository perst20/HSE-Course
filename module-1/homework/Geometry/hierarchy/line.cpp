#include "line.h"
#include "point.h"

bool Line::operator==(const Line &other) const {
    double coefficient;
    if (!isEqual(0, a) && !isEqual(0, other.a)) {
        coefficient = a / other.a;
    } else if (!isEqual(0, b) && !isEqual(0, other.b)) {
        coefficient = b / other.b;
    } else {
        return false;
    }
    return (isEqual(a / coefficient, other.a) && isEqual(b / coefficient, other.b) &&
            isEqual(c / coefficient, other.c));
}

bool Line::operator!=(const Line &rhs) const {
    return !(rhs == *this);
}

Line::Line(Point p1, Point p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -(a * p1.x + b * p1.y);
}

Line::Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

Line Line::getPerpendicularLine() const {
    return {-b, a, c};
}

Point Line::getPerpendicularVector() const {
    return {a, b};
}

Point Line::basePerpendicular(Point p) const {
    return intersect(Line(p, p + getPerpendicularVector()));
}

bool Line::isParallel(Line l) const {
    return Line{a, b, 0} == Line(l.a, l.b, 0);
}

Point Line::intersect(const Line &other) const {
    if (isParallel(other)) {
        return {INF, INF};
    }
    double q = a * other.b - b * other.a;
    return {(b * other.c - c * other.b) / q, (c * other.a - a * other.c) / q};
}
