#pragma once

#include <vector>
#include "polygon.h"
#include "point.h"

struct Rectangle : Polygon {
    Rectangle(Point const &p1, Point const &p2, double e);

    Point center() const;
};