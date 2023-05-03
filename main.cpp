#include <iostream>
#include "List/List.h"
#include "String/String.h"
#include "Graph/Graph.h"
#include "Graph/Point.h"
#include "PriorityQueueDijkstra/PriorityQueueDijkstra.h"

struct BFSNode {

    Point first;
    int second{};

    BFSNode()=default;

    BFSNode(const Point& p, int s) : first(p), second(s) {}

};


class GraphConstructor {

    char** vec;
    int sizeX;
    int sizeY;
    Graph& graph;

public:

    GraphConstructor(int x, int y, Graph& graph) : sizeX(x), sizeY(y), graph(graph) {
        vec = new char*[y];
        for(int i = 0; i < y; i++) {

            vec[i] = new char[x];
        }
    }

    ~GraphConstructor() {

        for(int i = 0; i < sizeY; i++) {

            delete[] vec[i];

        }

        delete[] vec;

    }

    bool isPosValid(int x, int y) {

        return y >= 0 && y < sizeY && x >= 0 && x < sizeX;

    }

    bool isPartOfName(char c) {

        return c != '.' && c != '*' && c != '#';

    }

    void getFirst(String& str, int x, int y) {

        char buff[32];
        int i = 0;

        while(isPosValid(x, y) && isPartOfName(vec[y][x])) {

            buff[i++] = vec[y][x++];

        }

        buff[i] = '\0';

        str = buff;

    }

    void getLast(String& str, int x, int y) {

        while(isPosValid(x, y) && isPartOfName(vec[y][x-1]) && x > 0) { x--; }

        getFirst(str, x, y);

    }

    bool isLast(int x, int y) {

        return  (isPosValid(x + 1, y)  && !isPartOfName(vec[y][x+1])) ||
                x + 1 == sizeX; //check at bounds

    }

    bool isFirst(int x, int y) {

        return  (isPosValid(x - 1, y)  && !isPartOfName(vec[y][x-1])) ||
                x == 0; //check at bounds


    }

    void getCityName(String& str, int x, int y) {

        int surroundings[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0},
                                  {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

        for(auto& surrounding : surroundings) {

            int dx = x + surrounding[0];
            int dy = y + surrounding[1];

            if(isPosValid(dx, dy) && isPartOfName(vec[dy][dx])) {

                if(isLast(dx, dy)) {

                    getLast(str, dx, dy);

                }
                else if(isFirst(dx, dy)) {

                    getFirst(str, dx, dy);

                }
            }
        }
    }

    bool isSurrounded(const Point& pos) {

        int surroundings[4][2] = {{0, -1},  {1, 0},{0, 1}, {-1, 0}};

        for(auto surrounding : surroundings) {

            int dx = surrounding[0];
            int dy = surrounding[1];
            if(isPosValid(pos.x + dx, pos.y + dy) && (vec[pos.y + dy][pos.x + dx] == '*' || vec[pos.y + dy][pos.x + dx] == '#' )) {

                return true;

            }
        }

        return false;

    }

    void floodFill(bool** visited, GraphNode& graphNode) {

        //no need to perform bfs if the city is not connected
        if(!isSurrounded(graphNode.pos)) { return; }

        for(int i = 0; i < sizeY; i++) {

            visited[i] = new bool[sizeX]();

        }

        List<BFSNode> stack;
        stack.addFirst(BFSNode(Point(graphNode.pos), 0));
        int surroundings[4][2] = {{0, -1},  {1, 0},{0, 1}, {-1, 0}};
        BFSNode c;

        while(!stack.isEmpty()) {

            if(!stack.getFirst()) { return; }
            c = stack.getFirst()->data;
            stack.removeFirst();

            if(c.first != graphNode.pos && isPosValid(c.first.x, c.first.y) && vec[c.first.y][c.first.x] == '*') {

                graph.addConnection(graphNode, c.first, c.second);

            }

            if(isPosValid(c.first.x, c.first.y) && (vec[c.first.y][c.first.x] == '#' || c.first == graphNode.pos)) {

                for(auto surrounding : surroundings) {

                    int dx = surrounding[0];
                    int dy = surrounding[1];

                    Point newP(c.first.x + dx, c.first.y + dy);

                    if (isPosValid(c.first.x + dx, c.first.y + dy) && !visited[newP.y][newP.x] &&
                        (vec[c.first.y + dy][c.first.x + dx] == '#' || vec[c.first.y + dy][c.first.x + dx] == '*') &&
                        newP != graphNode.pos) {

                        if(vec[newP.y][newP.x ] != '*')  { visited[newP.y][newP.x] = true; }

                        stack.pushBack(BFSNode(Point(newP), c.second + 1));

                    }
                }
            }
        }

        for(int i = 0; i < sizeY; i++) {

            delete[] visited[i];

        }
    }


    void createGraph() {
        int n;
        for(int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                n = getchar_unlocked();
                if(n < 32) n = getchar_unlocked();
                vec[i][j] = n;
            }
        }
        String name(32);
        for(int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                if(vec[i][j] == '*') {
                    getCityName(name, j, i);
                    graph.addNode(GraphNode(name, Point(j, i)));

                }
            }
        }
        bool** visited = new bool*[sizeY];

        for(int i = 0; i < graph.nodes.keys.size(); i++) {

            floodFill(visited, *graph.nodes.get(graph.nodes.keys[i]));

        }
        delete[] visited;

        int flightCount;
        scanf("%d", &flightCount);

        String source(32), dest(32), w(32);
        int weigth;

        for(int i = 0; i < flightCount; i++) {

            source.read();
            dest.read();
            w.read();
            weigth = atoi(w);

            graph.addConnectionFlight(source, dest, weigth);

        }

    }

};


void dijkstraPrioQueue(Graph& graph, const String& source, HashMap<String>& path, PriorityQueueDijkstra& pq) {

    path.clear();

    auto iter = graph.nodes.getKeys();
    for(int i = 0; i < iter.size(); i++) {

        GraphNode* graphNode = graph.nodes.get(iter[i]);
        if(graphNode->name == source) {  graph.nodes.get(graphNode->name)->weigth = 0; }
        else { graph.nodes.get(graphNode->name)->weigth = INF; }
        graphNode->visited = false;
        path.set(graphNode->name, "");

    }

    pq.push(std::move(DijkstraNode(source, 0)));
    DijkstraNode currentNode;

    while(!pq.empty()) {

        currentNode = pq.top();
        pq.pop();

        if(graph.nodes.get(currentNode.name)->visited) continue;
        graph.nodes.get(currentNode.name)->visited = true;

        Node<Connection>* connection = graph.nodes.get(currentNode.name)->connections.getFirst();
        for(;connection; connection = connection->next) {

            int dist = currentNode.weigth + connection->data.weigth;
            if(dist < graph.nodes.get(connection->data.name)->weigth) {

                graph.nodes.get(connection->data.name)->weigth = dist;
                *path.get(connection->data.name) = currentNode.name;
                pq.push(std::move(DijkstraNode(connection->data.name, graph.nodes.get(connection->data.name)->weigth)));

            }
        }
    }
}


void dijkstra(Graph& graph, const String& source, HashMap<String>& path) {

    path.clear();

    auto iter = graph.nodes.getKeys();
    for(int i = 0; i < iter.size(); i++) {

        GraphNode* graphNode = graph.nodes.get(iter[i]);
        if(graphNode->name == source) { graphNode->weigth = 0; graphNode->visited = false; }
        else { graphNode->weigth = INF; graphNode->visited = false; }
        path.set(graphNode->name, "");

    }
    int i = 0;
    while(i < iter.size()) {

        i++;
        GraphNode *currentNode = graph.nodes.get(iter[0]);
        for(int j = 0; j < iter.size(); j++) {

            if(currentNode->visited) { currentNode = graph.nodes.get(iter[j]); }

            if (graph.nodes.get(iter[j])->weigth < currentNode->weigth && !graph.nodes.get(iter[j])->visited) {

                currentNode = graph.nodes.get(iter[j]);

            }
        }

        Node<Connection>* connection = currentNode->connections.getFirst();
        for(;connection; connection = connection->next) {

            int dist = currentNode->weigth + connection->data.weigth;
            if(dist < graph.nodes.get(connection->data.name)->weigth) {

                graph.nodes.get(connection->data.name)->weigth = dist;
                *path.get(connection->data.name) = currentNode->name;

            }
        }

        currentNode->visited = true;

    }
}



void printPath(HashMap<String>& path, const String& source, const String& dest) {

    List<String> stack;
    String target = dest;
    String next = *path.get(target);

    if(path.get(target) && !(next == source) || target == source) {

        while(path.get(target) && target != "") {

            if(target.length()) stack.addFirst(target);
            target = *path.get(target);

        }
    }

    while(stack.getFirst()) {

        Node<String>* node = stack.getFirst();

        if(!(node->data == source) && !(node->data == dest))  std::cout << node->data << " ";
        stack.removeFirst();

    }

}


int main() {

    int x, y;
    Graph graph;
    scanf("%d %d", &x, &y);

    GraphConstructor graphConstructor(x, y, graph);

    graphConstructor.createGraph();

    int queryCount;
    scanf("%d", &queryCount);

    String prevSource;
    int queryType;

    HashMap<String> parentArray;
    PriorityQueueDijkstra pq;

    String source(32), dest(32);

    for(int i = 0; i < queryCount; i++) {

        source.read();
        dest.read();
        scanf("%d", &queryType);

        if(!(source == prevSource) || queryType == 1) {

            dijkstraPrioQueue(graph, source, parentArray, pq);

        }

        printf("%d", graph.nodes.get(dest)->weigth);
        if(queryType == 1) {

            printf(" ");
            printPath(parentArray, source, dest);

        }

        prevSource = source;
        printf("\n");
    }

    return 0;
}