#include <complex>
#include "point.h"

const double PI = 3.1415926, EPS = 10e-6, INF = HUGE_VAL;

bool isEqual(double first, double second) {
    return std::abs(first - second) < EPS;
}

bool Point::operator==(const Point &other) const {
    return isEqual(x, other.x) &&
           isEqual(y, other.y);
}

bool Point::operator!=(const Point &other) const {
    return !(other == *this);
}

Point Point::operator-() const {
    return {-x, -y};
}

Point Point::operator+(const Point &other) const {
    return {x + other.x, y + other.y};
}

Point Point::operator-(const Point &other) const {
    return *this + (-other);
}

Point &Point::operator+=(const Point &other) {
    return *this = *this + other;
}

Point Point::operator-=(const Point &other) {
    return *this += -other;
}

double Point::abs() const {
    return std::sqrt(squareAbs());
}

double Point::squareAbs() const {
    return x * x + y * y;
}

Point Point::normalized() const {
    return {x / abs(), y / abs()};
}

Point Point::operator*(const double &sc) const {
    return {x * sc, y * sc};
}

Point Point::operator/(const double &sc) const {
    return {x / sc, y / sc};
}

Point &Point::operator*=(const double &sc) {
    return *this = *this * sc;
}

Point &Point::operator/=(const double &sc) {
    return *this = *this / sc;
}

double Point::crossProduct(const Point &other) const{
    return x * other.y - other.x * y;
}

double Point::dotProduct(const Point &other) const{
    return x* other.x + y * other.y;
}

Point Point::rotate(double angle, Point pivot) const {
    double s = sin(angle), c = cos(angle);
    Point tmp = *this - pivot;
    Point rotatedTmp{tmp.x * c - tmp.y * s, tmp.x * s + tmp.y * c};
    return rotatedTmp + pivot;
}

Point::Point(double x, double y) : x(x), y(y) {}
