#pragma once

#include "ellipse.h"

struct Circle : Ellipse {
    Circle(Point center, double radius);

    double radius() const;

    double perimeter() const override;

    double area() const override;
};