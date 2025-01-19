#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/**
 * @brief   Class representing an undirected graph.
 */
class Graph {
private:
    int vertices;                      ///< عدد الرؤوس في الرسم البياني
    vector< vector<int> > adjList;       ///< قائمة الجيران لكل رأس

public:
    /**
     * @brief   Constructor to initialize the graph with the number of vertices.
     * @param   vertices  عدد الرؤوس في الرسم البياني
     */
    Graph(int vertices) {
        this->vertices = vertices;
        adjList.resize(vertices);
    }

    /**
     * @brief   Add an edge to the graph.
     * @param   u   الرأس الأول.
     * @param   v   الرأس الثاني.
     */
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // لأن الرسم البياني غير موجه
    }

    /**
     * @brief   Depth First Search (DFS) traversal starting from a given node.
     * @param   startVertex   الرأس الذي تبدأ منه عملية الاستكشاف
     */
    void dfs(int startVertex) {
        vector<bool> visited(vertices, false); // مصفوفة لتتبع الرؤوس التي تم زيارتها
        stack<int> s; // استخدام مكدس لدعم عملية DFS

        // إضافة الرأس الأول إلى المكدس
        s.push(startVertex);

        while (!s.empty()) {
            // استخراج الرأس من المكدس
            int vertex = s.top();
            s.pop();

            // إذا لم يكن قد تم زيارته مسبقًا
            if (!visited[vertex]) {
                visited[vertex] = true;
                cout << vertex << " "; // طباعة الرأس الذي تم زيارته

                // إضافة جميع الجيران غير المزورين إلى المكدس
                for (size_t i = 0; i < adjList[vertex].size(); ++i) {
                    int neighbor = adjList[vertex][i];
                    if (!visited[neighbor]) {
                        s.push(neighbor);
                    }
                }
            }
        }
    }
};

/**
 * @brief   Main function to demonstrate DFS on a graph.
 */
int main() {
    // إنشاء رسم بياني مع 5 رؤوس
    Graph g(5);

    // إضافة الحواف
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    
    cout << "DFS starting from vertex 0: ";
    g.dfs(0); // بدء الاستكشاف من الرأس 0

    return 0;
}
