#include <cstddef>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "polygon.h"

size_t Polygon::verticesCount() const {
    return vertices_.size();
}

std::vector<Point> Polygon::getVertices() const {
    return vertices_;
}

bool Polygon::isConvex() const {
    size_t count = verticesCount();
    int prev = 0;
    for (size_t i = 0; i < count; ++i) {
        Point p0 = vertices_[i],
                p1 = vertices_[(i + count - 1) % count],
                p2 = vertices_[(i + 1) % count];
        double product = (p1 - p0).crossProduct(p2 - p0);
        if (isEqual(product, 0))
            continue;
        if (product > 0 && prev < 0 || product < 0 && prev > 0)
            return false;
        if (prev == 0)
            prev = product > 0 ? 1 : -1;
    }
    return true;
}

Polygon::Polygon(const std::vector<Point> &points) {
    if (points.size() < 3)
        throw std::invalid_argument("Polygon must have 3 or more vertices");
    vertices_ = points;
}

double Polygon::perimeter() const {
    double per = 0;
    Point prev = vertices_.back();
    for (auto const &v : vertices_) {
        per += (v - prev).abs();
        prev = v;
    }
    return per;
}

double Polygon::area() const {
    double area = 0;
    Point prev = vertices_.back();
    for (auto const &v : vertices_) {
        area += prev.crossProduct(v);
        prev = v;
    }
    return std::abs(area);
}

bool Polygon::operator==(const Shape &another) const {
    auto *now = dynamic_cast<Polygon const *>(&another);
    if (now == nullptr)
        return false;
    if (verticesCount() != now->verticesCount())
        return false;
    auto other_vertices = now->getVertices();
    if (isEqualVertices(vertices_, other_vertices))
        return true;
    std::reverse(other_vertices.begin(), other_vertices.end());
    return isEqualVertices(vertices_, other_vertices);
}

bool Polygon::isCongruentTo(const Shape &another) const {
    auto *now = dynamic_cast<Polygon const *>(&another);
    if (now == nullptr)
        return false;
    if (verticesCount() != now->verticesCount())
        return false;
    auto other_vertices = now->getVertices();
    if (isCongruentVertices(vertices_, other_vertices))
        return true;
    std::reverse(other_vertices.begin(), other_vertices.end());
    return isCongruentVertices(vertices_, other_vertices);
}

bool Polygon::isSimilarTo(const Shape &another) const {
    auto *now = dynamic_cast<Polygon const *>(&another);
    if (now == nullptr)
        return false;
    if (verticesCount() != now->verticesCount())
        return false;
    auto other_vertices = now->getVertices();
    if (isSimilarVertices(vertices_, other_vertices))
        return true;
    std::reverse(other_vertices.begin(), other_vertices.end());
    return isSimilarVertices(vertices_, other_vertices);
}

bool Polygon::containsPoint(Point point) const {
    double sum = 0;
    auto prev = vertices_.back();
    for (auto i : vertices_) {
        auto now1 = i - point;
        auto now2 = prev - point;
        auto now3 = std::atan2(now1.crossProduct(now2), now1.dotProduct(now2));
        sum += now3;
        prev = i;
        if (isEqual(std::abs(now3), PI)) return true;
        if (point.x == i.x && point.y == i.y) return true;
    }
    return !(isEqual(sum, 0));
}

void Polygon::rotate(Point center, double angle) {
    angle /= 360;
    angle *= 2 * PI;
    for (auto &vertex : vertices_)
        vertex = vertex.rotate(angle, center);
}

void Polygon::reflex(Point center) {
    for (auto &vertex : vertices_)
        vertex = center - (vertex - center);
}

void Polygon::reflex(Line axis) {
    for (auto &vertex : vertices_) {
        auto reflex_point = axis.basePerpendicular(vertex);
        vertex = reflex_point - (vertex - reflex_point);
    }
}

void Polygon::scale(Point center, double coefficient) {
    for (auto &vertex : vertices_) {
        vertex = center + (vertex - center) * coefficient;
    }
}

bool Polygon::isEqualVertices(std::vector<Point> const &vertices1, std::vector<Point> const &vertices2) const {
    size_t count = verticesCount();
    for (size_t shift = 0; shift < count; ++shift) {
        bool flag = false;
        for (size_t i = 0; i < count; ++i) {
            if (vertices1[i] == vertices2[(i + shift) % count])
                continue;
            flag = true;
            break;
        }
        if (!flag) return true;
    }
    return false;
}

bool Polygon::isCongruentVertices(const std::vector<Point> &vertices1, const std::vector<Point> &vertices2) const {
    size_t count = verticesCount();
    for (size_t shift = 0; shift < count; ++shift) {
        bool flag = false;
        for (size_t i = 0; i < count; ++i) {
            Point v1 = vertices1[(i + 1) % count] - vertices1[i],
                    v2 = vertices1[(i - 1 + count) % count] - vertices1[i],
                    av1 = vertices2[(i + 1 + shift) % count] - vertices2[(i + shift) % count],
                    av2 = vertices2[(i - 1 + shift + count) % count] - vertices2[(i + shift) % count];
            if (isEqual(std::abs(atan2(v2.y, v2.x) - atan2(v1.y, v1.x)),
                        std::abs(atan2(av2.y, av2.x) - atan2(av1.y, av1.x)))
                && isEqual((vertices1[(i + 1) % count] - vertices1[i]).abs(),
                           (vertices2[(i + 1 + shift) % count] - vertices2[(i + shift) % count]).abs()))
                continue;
            flag = true;
            break;
        }
        if (!flag) return true;
    }
    return false;
}

bool Polygon::isSimilarVertices(const std::vector<Point> &vertices1, const std::vector<Point> &vertices2) const {
    size_t count = verticesCount();
    for (size_t shift = 0; shift < count; ++shift) {
        bool flag = false;
        for (size_t i = 0; i < count; ++i) {
            Point v1 = vertices1[(i + 1) % count] - vertices1[i],
                    v2 = vertices1[(i - 1 + count) % count] - vertices1[i],
                    av1 = vertices2[(i + 1 + shift) % count] - vertices2[(i + shift) % count],
                    av2 = vertices2[(i - 1 + shift + count) % count] - vertices2[(i + shift) % count];
            if (isEqual(std::abs(atan2(v2.y, v2.x) - atan2(v1.y, v1.x)),
                        std::abs(atan2(av2.y, av2.x) - atan2(av1.y, av1.x))))
                continue;
            flag = true;
            break;
        }
        if (!flag) return true;
    }
    return false;
}
