#pragma once
#include <string.h>
#include <string>

struct Point {

    int x;
    int y;

    Point() : x(), y() {}

    Point(int x, int y) : x(x), y(y) {}

    Point(const Point& p) {

        x = p.x;
        y = p.y;

    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p) {

        out << "(" << p.x << ", " << p.y << ")";
        return out;

    }

    bool operator==(const Point& other) const {

        return x == other.x && y == other.y;

    }

    bool operator!=(const Point& other) const {

        return !(*this == other);

    }

};