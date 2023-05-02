#include "../String/String.h"

struct DijkstraNode {

    String name;
    int weigth{};

    DijkstraNode() = default;

    DijkstraNode(String name, int weigth) : name(std::move(name)), weigth(weigth) {}

};
