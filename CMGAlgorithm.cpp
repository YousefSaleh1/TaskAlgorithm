#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

/**
 * Class representing a disjoint-set (Union-Find) data structure.
 * Used for efficiently managing and merging sets during the algorithm.
 */
class UnionFind
{
public:
    vector<int> parent, rank;

    UnionFind(int size)
    {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }

    /**
     * Find the root of the set containing `x`.
     * Uses path compression for optimization.
     *
     * @param x The element whose root is to be found.
     * @return The root of the set containing `x`.
     */
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    /**
     * Union the sets containing `x` and `y`.
     * Uses union by rank for optimization.
     *
     * @param x The first element.
     * @param y The second element.
     */
    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

/**
 * Class representing a graph.
 * Contains methods to represent the graph using Adjacency Matrix, Adjacency Array, and Adjacency List.
 */
class Graph
{
public:
    int vertices;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> adjArray;
    vector<vector<pair<int, int>>> adjList;

    Graph(int v) : vertices(v)
    {
        adjMatrix.resize(v, vector<int>(v, 0));
        adjArray.resize(v);
        adjList.resize(v);
    }

    /**
     * Adds an edge between two vertices.
     *
     * @param u The starting vertex.
     * @param v The ending vertex.
     * @param weight The weight of the edge.
     */
    void addEdge(int u, int v, int weight)
    {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;

        adjArray[u].push_back(v);
        adjArray[v].push_back(u);

        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    /**
     * Prints the graph using Adjacency Matrix representation.
     */
    void printAdjMatrix()
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    /**
     * Prints the graph using Adjacency Array representation.
     */
    void printAdjArray()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << ": ";
            for (int v : adjArray[i])
            {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    /**
     * Prints the graph using Adjacency List representation.
     */
    void printAdjList()
    {
        for (int i = 0; i < vertices; i++)
        {
            cout << i << ": ";
            for (auto &neighbor : adjList[i])
            {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

/**
 * Cheriyan-Mehlhorn-Gabow algorithm to find MST.
 *
 * @param graph The graph on which MST is to be found.
 * @param uf UnionFind data structure for set management.
 */
void CheriyanMehlhornGabow(Graph &graph, UnionFind &uf)
{
    // Sorting edges based on weight
    vector<pair<int, pair<int, int>>> edges;
    for (int u = 0; u < graph.vertices; u++)
    {
        for (int v = u + 1; v < graph.vertices; v++)
        {
            if (graph.adjMatrix[u][v] != 0)
            {
                edges.push_back({graph.adjMatrix[u][v], {u, v}});
            }
        }
    }
    sort(edges.begin(), edges.end());

    vector<pair<int, int>> mstEdges;
    int mstWeight = 0;

    // Processing edges in ascending order of weight
    for (auto &edge : edges)
    {
        int u = edge.second.first;
        int v = edge.second.second;
        int weight = edge.first;

        if (uf.find(u) != uf.find(v))
        {
            uf.unionSets(u, v);
            mstEdges.push_back({u, v});
            mstWeight += weight;
        }
    }

    // Output the MST edges and their total weight
    cout << "MST edges:\n";
    for (auto &edge : mstEdges)
    {
        cout << edge.first << " - " << edge.second << endl;
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}

/**
 * Function to generate a random graph.
 *
 * @param vertices Number of vertices in the graph.
 * @param edges Number of edges in the graph.
 * @param graph The graph object to populate.
 */
void generateRandomGraph(int vertices, int edges, Graph &graph)
{
    srand(time(0));
    for (int i = 0; i < edges; i++)
    {
        int u = rand() % vertices;
        int v = rand() % vertices;
        int weight = rand() % 10 + 1;
        graph.addEdge(u, v, weight);
    }
}

int main()
{
    int vertices = 5;
    int edges = 7;

    Graph graph(vertices);
    generateRandomGraph(vertices, edges, graph);

    // Display the graph in different formats
    cout << "Adjacency Matrix:\n";
    graph.printAdjMatrix();
    cout << "\nAdjacency Array:\n";
    graph.printAdjArray();
    cout << "\nAdjacency List:\n";
    graph.printAdjList();

    // Running Cheriyan-Mehlhorn-Gabow algorithm
    UnionFind uf(vertices);
    CheriyanMehlhornGabow(graph, uf);

    return 0;
}
