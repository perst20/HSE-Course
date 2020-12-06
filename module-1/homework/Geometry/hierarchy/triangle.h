#pragma once

#include <vector>
#include "polygon.h"
#include "circle.h"

struct Triangle : Polygon {
    Triangle(Point const &p1, Point const &p2, Point const &p3);

    Circle circumscribedCircle() const;

    Circle inscribedCircle() const;

};