#pragma once

#include "point.h"

struct Line {
    Line(double _a, double _b, double _c);

    Line(Point p1, Point p2);

    bool operator==(const Line &other) const;

    bool operator!=(const Line &rhs) const;

    Line getPerpendicularLine() const;

    Point getPerpendicularVector() const;

    Point basePerpendicular(Point p) const;

    bool isParallel(Line l) const;

    Point intersect(const Line &other) const;

private:
    double a, b, c;
};