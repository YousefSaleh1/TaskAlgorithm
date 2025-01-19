#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

/** 
 * @brief Represents a directed graph and provides methods to find strongly connected components (SCC).
 */
class Graph {
private:
    int vertices;                              // Number of vertices in the graph
    std::vector<std::vector<int>> adjList;    // Adjacency list representation of the graph

    // Helper method for the first DFS to fill the stack
    void fillOrder(int vertex, std::vector<bool>& visited, std::stack<int>& stack);

    // Helper method to perform DFS on the transposed graph
    void dfsOnTranspose(int vertex, std::vector<bool>& visited, std::vector<int>& component);

    // Transposes the graph
    Graph getTranspose();

public:
    /**
     * @brief Constructs a graph with a specified number of vertices.
     * @param vertices The number of vertices in the graph.
     */
    explicit Graph(int vertices);

    /**
     * @brief Adds a directed edge from source to destination.
     * @param src The source vertex.
     * @param dest The destination vertex.
     */
    void addEdge(int src, int dest);

    /**
     * @brief Finds and prints all strongly connected components in the graph.
     */
    void findStronglyConnectedComponents();
};

Graph::Graph(int vertices) : vertices(vertices), adjList(vertices) {}

void Graph::addEdge(int src, int dest) {
    adjList[src].push_back(dest);
}

void Graph::fillOrder(int vertex, std::vector<bool>& visited, std::stack<int>& stack) {
    visited[vertex] = true;
    for (int neighbor : adjList[vertex]) {
        if (!visited[neighbor]) {
            fillOrder(neighbor, visited, stack);
        }
    }
    stack.push(vertex);
}

Graph Graph::getTranspose() {
    Graph transposed(vertices);
    for (int i = 0; i < vertices; i++) {
        for (int neighbor : adjList[i]) {
            transposed.addEdge(neighbor, i);
        }
    }
    return transposed;
}

void Graph::dfsOnTranspose(int vertex, std::vector<bool>& visited, std::vector<int>& component) {
    visited[vertex] = true;
    component.push_back(vertex);
    for (int neighbor : adjList[vertex]) {
        if (!visited[neighbor]) {
            dfsOnTranspose(neighbor, visited, component);
        }
    }
}

void Graph::findStronglyConnectedComponents() {
    std::stack<int> stack;
    std::vector<bool> visited(vertices, false);

    // Step 1: Fill vertices in stack according to their finishing times
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            fillOrder(i, visited, stack);
        }
    }

    // Step 2: Get the transposed graph
    Graph transposed = getTranspose();

    // Step 3: Process all vertices in order defined by the stack
    std::fill(visited.begin(), visited.end(), false);
    while (!stack.empty()) {
        int vertex = stack.top();
        stack.pop();

        if (!visited[vertex]) {
            std::vector<int> component;
            transposed.dfsOnTranspose(vertex, visited, component);
            std::cout << "SCC: ";
            for (int node : component) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main() {
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    std::cout << "Strongly Connected Components:\n";
    g.findStronglyConnectedComponents();

    return 0;
}
