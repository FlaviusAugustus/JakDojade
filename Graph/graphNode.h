#pragma once
#include <utility>
#include "../String/String.h"
#include "../List/List.h"
#include "Connection.h"
#include "Point.h"
#define INF 999999999

struct GraphNode {

    String name;
    Point pos;
    int weigth;
    bool visited;
    List<Connection> connections;

    GraphNode(String name, const Point& pos) : name(std::move(name)), pos(pos), weigth(INF), visited(false)  {}

    GraphNode(String name, int weigth) : name(std::move(name)), weigth(weigth), visited(false), pos(Point(0, 0)) {}

    GraphNode() {};

    friend std::ostream& operator<<(std::ostream& out, const GraphNode& node) {

        out << "Node: " << node.name << node.pos << " Connections: " << node.connections << std::endl;
        return out;
    }

};


