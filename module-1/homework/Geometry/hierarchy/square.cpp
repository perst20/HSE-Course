#include "square.h"

Square::Square(Point p1, Point p2) : Rectangle(p1, p2, 1) {}

Circle Square::circumscribedCircle() const {
    return {center(), (vertices_[0] - vertices_[2]).abs() / 2};
}

Circle Square::inscribedCircle() const {
    return {center(), (vertices_[0] - vertices_[1]).abs() / 2};
}
