#pragma once

#include <utility>
#include <complex>
#include "point.h"
#include "line.h"
#include "shape.h"

struct Ellipse : Shape {
    Ellipse(Point const &p1, Point const &p2, double sum);

    std::pair<Point, Point> focuses() const;

    std::pair<Line, Line> directrices() const;

    double eccentricity() const;

    Point center() const;

    double perimeter() const override;

    double area() const override;

    bool operator==(const Shape &another) const override;

    bool isCongruentTo(const Shape &another) const override;

    bool isSimilarTo(const Shape &another) const override;

    bool containsPoint(Point point) const override;

    void rotate(Point center, double angle) override;

    void reflex(Point center) override;

    void reflex(Line axis) override;

    void scale(Point center, double coefficient) override;

    double getB() const;

    double getA() const;

private:
    Point f1, f2;
    double sum_;
};
