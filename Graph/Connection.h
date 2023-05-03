#include <utility>

#include "../String/String.h"
#include "Point.h"

struct Connection {

    String name;
    int weigth;

    Connection() : weigth(), name() {}

    Connection(String  n, int w) : name(std::move(n)), weigth(w) {}

    Connection(const Connection& other) {

        name = other.name;
        weigth = other.weigth;

    }

    Connection& operator=(const Connection& other) {

        name = other.name;
        weigth = other.weigth;

        return *this;

    }

    Connection& operator=(Connection&& other) {

        std::swap(name, other.name);
        weigth = other.weigth;

        other.weigth= 0;
        other.name = "";

        return *this;

    }

    friend std::ostream& operator<<(std::ostream& out, const Connection& con) {

        out << "-> " << con.name << " w: " << con.weigth << " |";
        return out;

    }

};


