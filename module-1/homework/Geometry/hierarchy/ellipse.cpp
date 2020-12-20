#include "ellipse.h"

Ellipse::Ellipse(const Point &p1, const Point &p2, double sum) : f1(p1), f2(p2), sum_(sum) {}

std::pair<Point, Point> Ellipse::focuses() const {
    return {f1, f2};
}

std::pair<Line, Line> Ellipse::directrices() const {
    Point c = center();
    Line l1{f1, f2};
    Line l2{c, l1.getPerpendicularVector() + c};
    return {l1, l2};
}

double Ellipse::eccentricity() const {
    return (f2 - f1).abs() / sum_;
}

Point Ellipse::center() const {
    return (f1 + f2) / 2;
}

double Ellipse::perimeter() const {
    double a = getA(), b = getB();
    return 4 * (PI * a * b + (a - b)) / (a + b);
}

double Ellipse::area() const {
    double a = getA(), b = getB();
    return PI * a * b;
}

bool Ellipse::operator==(const Shape &another) const {
    auto *now = dynamic_cast<Ellipse const *>(&another);
    if (now == nullptr)
        return false;
    return focuses() == now->focuses() && isEqual(sum_, now->sum_);
}

bool Ellipse::isCongruentTo(const Shape &another) const {
    auto *now = dynamic_cast<Ellipse const *>(&another);
    if (now == nullptr)
        return false;
    return eccentricity() == now->eccentricity() && isEqual(sum_, now->sum_);
}

bool Ellipse::isSimilarTo(const Shape &another) const {
    auto *now = dynamic_cast<Ellipse const *>(&another);
    if (now == nullptr)
        return false;
    return eccentricity() == now->eccentricity();
}

bool Ellipse::containsPoint(Point point) const {
    double a = getA(), b = getB();
    return point.x * point.x / a * a + point.y * point.y / b * b <= 1;
}

void Ellipse::rotate(Point center, double angle) {
    angle /= 360;
    angle *= 2 * PI;
    f1 = f1.rotate(angle, center);
    f2 = f2.rotate(angle, center);
}

void Ellipse::reflex(Point center) {
    f1 = center - (f1 - center);
    f2 = center - (f2 - center);
}

void Ellipse::reflex(Line axis) {
    f1 = axis.basePerpendicular(f1) - (f1 - axis.basePerpendicular(f1));
    f2 = axis.basePerpendicular(f2) - (f2 - axis.basePerpendicular(f2));
}

void Ellipse::scale(Point center, double coefficient) {
    f1 = center + (f1 - center) * coefficient;
    f2 = center + (f2 - center) * coefficient;
    sum_ *= coefficient;
}

double Ellipse::getB() const {
    return getA() * std::sqrt(1 - eccentricity() * eccentricity());
}

double Ellipse::getA() const {
    return sum_ / 2;
}
