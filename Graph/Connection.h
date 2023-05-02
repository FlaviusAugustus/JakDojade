#include <utility>

#include "../String/String.h"
#include "Point.h"

struct Connection {

    String name;
    int weigth;
    Point pos;

    Connection() : weigth(), name() {}

    Connection(const String& n, int w, const Point& p) : name(n), weigth(w) {

        pos.x = p.x;
        pos.y = p.y;

    }

    Connection(const Connection& other) {

        name = other.name;
        weigth = other.weigth;
        pos = other.pos;

    }

    Connection& operator=(const Connection& other) {

        name = other.name;
        weigth = other.weigth;
        pos = other.pos;

        return *this;

    }

    Connection& operator=(Connection&& other) {

        std::swap(name, other.name);
        weigth = other.weigth;
        pos = other.pos;

        other.weigth= 0;
        other.name = "";

        return *this;

    }

    friend std::ostream& operator<<(std::ostream& out, const Connection& con) {

        out << "-> " << con.name << " w: " << con.weigth << " |";
        return out;

    }

};


