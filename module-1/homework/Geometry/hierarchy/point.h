#pragma once

const extern double PI, EPS, INF;

bool isEqual(double first, double second);

struct Point {
    double x;
    double y;

    Point() = default;

    Point(double x, double y);

    bool operator==(const Point &other) const;

    bool operator!=(const Point &other) const;

    Point operator-() const;

    Point operator+(Point const &other) const;

    Point operator-(Point const &other) const;

    Point &operator+=(Point const &other);

    Point operator-=(Point const &other);

    Point operator*(double const &sc) const;

    Point operator/(double const &sc) const;

    Point &operator*=(double const &sc);

    Point &operator/=(double const &sc);

    double crossProduct(Point const &other) const;

    double dotProduct(Point const &other) const;

    double abs() const;

    double squareAbs() const;

    Point normalized() const;

    Point rotate(double angle, Point pivot = {}) const;
};