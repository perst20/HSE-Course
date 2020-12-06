#pragma once

#include "rectangle.h"
#include "circle.h"

struct Square : Rectangle {
    Square(Point p1, Point p2);

    Circle circumscribedCircle() const;

    Circle inscribedCircle() const;
};