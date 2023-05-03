#include "Graph.h"

#include <utility>

int Graph::count = 0;

void Graph::addNode(const GraphNode& node) {

    nodes.set(node.name, node);

}

void Graph::checkForConnectionDuplicates(GraphNode& node, const Connection& connection) {

    Node<Connection>* ptr = node.connections.getFirst();
    bool wasFound = false;
    if(ptr) {
        for (; ptr; ptr = ptr->next) {

            if (ptr->data.name == connection.name) {

                ptr->data.weigth = connection.weigth > ptr->data.weigth ? ptr->data.weigth : connection.weigth;
                wasFound = true;
                break;

            }

        }
    }
    if(!wasFound) { node.connections.pushBack(connection);}

}

void Graph::addConnection(GraphNode& node, const Point& p, int w) {

    GraphNode* graphNode = nodes.get(node.name);
    String name = findConnection(p);
    checkForConnectionDuplicates(*graphNode, Connection(name, w));
    //graphNode->connections.pushBack(newConnection);

}

void Graph::addConnectionFlight(const String& source, String dest, int weigth) {

    GraphNode* graphNode = nodes.get(source);
    //checkForConnectionDuplicates(*graphNode, newConnection);
    graphNode->connections.pushBack(Connection(std::move(dest), weigth));

}

String Graph::findConnection(const Point& pos) {

    for(int i = 0; i < nodes.keys.size(); i++) {

        String name = nodes.keys[i];
        auto node = nodes.get(name);

        if(node->pos == pos) { return node->name; }

    }

    return " ";

}

std::ostream& operator<<(std::ostream& out, Graph& g) {

    out << g.nodes.collisionCount() << std::endl;

    int index;

    for(int i = 0; i < g.nodes.keys.size(); i++) {

         index = g.nodes.hash(g.nodes.keys[i]);
         out << g.nodes.buckets[index]->getFirst()->data.value.weigth << " " << g.nodes.buckets[index]->getFirst()->data.value;

    }

    return out;
}

