#include "graphNode.h"
#include "../HashMap/HashMap.h"
#include <vector>

class Graph {

    public:

    HashMap<GraphNode> nodes;

    static int count;

    void addNode(const GraphNode& node);

    void addConnection(GraphNode& node, const Point& pos, int weigth);

    void addConnectionFlight(const String& source, String dest, int weigth);

    void checkForConnectionDuplicates(GraphNode& node, const Connection& connection);

    String findConnection(const Point& pos);

    friend std::ostream& operator<<(std::ostream& out, Graph& g);

};


