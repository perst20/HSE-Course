#pragma once

#include "point.h"
#include "shape.h"

struct Polygon : Shape {
    explicit Polygon(std::vector<Point> const &points);

    size_t verticesCount() const;

    std::vector<Point> getVertices() const;

    bool isConvex() const;

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

protected:
    std::vector<Point> vertices_;

    Polygon() = default;

private:
    bool isEqualVertices(std::vector<Point> const &vertices1, std::vector<Point> const &vertices2) const;
    bool isCongruentVertices(std::vector<Point> const &vertices1, std::vector<Point> const &vertices2) const;
    bool isSimilarVertices(std::vector<Point> const &vertices1, std::vector<Point> const &vertices2) const;
};