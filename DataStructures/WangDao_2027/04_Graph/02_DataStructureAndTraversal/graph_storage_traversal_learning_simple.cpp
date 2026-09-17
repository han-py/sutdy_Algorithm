#include <algorithm>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace {

constexpr int INF = 1000000000;

struct MatrixGraph {
    vector<char> vertices;
    vector<vector<int>> matrix;
    bool directed = false;
};

struct ListGraph {
    vector<char> vertices;
    vector<vector<pair<int, int>>> adj;
    bool directed = false;
};

struct MultiListGraph {
    struct EdgeBox {
        int ivex = -1;
        int jvex = -1;
        int ilink = -1;
        int jlink = -1;
        int weight = 1;
    };

    struct VertexNode {
        char data = '?';
        int firstedge = -1;
    };

    vector<VertexNode> vertices;
    vector<EdgeBox> edges;
};

struct OrthogonalGraph {
    struct ArcBox {
        int tailvex = -1;
        int headvex = -1;
        int tlink = -1;
        int hlink = -1;
        int weight = 1;
    };

    struct VertexNode {
        char data = '?';
        int firstin = -1;
        int firstout = -1;
    };

    vector<VertexNode> vertices;
    vector<ArcBox> arcs;
};

string edgeNameUndirected(char a, char b) {
    return string(1, a) + "-" + string(1, b);
}

string edgeNameDirected(char a, char b) {
    return string(1, a) + "→" + string(1, b);
}

string emptyText(int index) {
    return index == -1 ? string("∅") : to_string(index);
}

void banner(const string& title) {
    cout << "\n============================================================\n";
    cout << title << '\n';
    cout << "============================================================\n";
}

void subtitle(const string& title) {
    cout << "\n【" << title << "】\n";
}

string pathText(const vector<char>& vertices, const vector<int>& order) {
    if (order.empty()) return "(空)";
    string s;
    for (size_t i = 0; i < order.size(); ++i) {
        if (i) s += " -> ";
        s += vertices[order[i]];
    }
    return s;
}

MatrixGraph buildMatrixGraph(const vector<char>& vertices,
                             const vector<tuple<int, int, int>>& edges,
                             bool directed) {
    MatrixGraph g;
    g.vertices = vertices;
    g.directed = directed;
    int n = static_cast<int>(vertices.size());
    g.matrix.assign(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) g.matrix[i][i] = 0;
    for (const auto& [u, v, w] : edges) {
        g.matrix[u][v] = min(g.matrix[u][v], w);
        if (!directed) g.matrix[v][u] = min(g.matrix[v][u], w);
    }
    return g;
}

ListGraph buildListGraph(const vector<char>& vertices,
                         const vector<tuple<int, int, int>>& edges,
                         bool directed) {
    ListGraph g;
    g.vertices = vertices;
    g.directed = directed;
    g.adj.assign(vertices.size(), {});
    for (const auto& [u, v, w] : edges) {
        g.adj[u].push_back({v, w});
        if (!directed) g.adj[v].push_back({u, w});
    }
    return g;
}

MultiListGraph buildMultiListGraph(const vector<char>& vertices,
                                   const vector<tuple<int, int, int>>& edges) {
    MultiListGraph g;
    for (char c : vertices) g.vertices.push_back({c, -1});
    for (const auto& [u, v, w] : edges) {
        int idx = static_cast<int>(g.edges.size());
        g.edges.push_back({u, v, g.vertices[u].firstedge, g.vertices[v].firstedge, w});
        g.vertices[u].firstedge = idx;
        g.vertices[v].firstedge = idx;
    }
    return g;
}

OrthogonalGraph buildOrthogonalGraph(const vector<char>& vertices,
                                     const vector<tuple<int, int, int>>& edges) {
    OrthogonalGraph g;
    for (char c : vertices) g.vertices.push_back({c, -1, -1});
    for (const auto& [u, v, w] : edges) {
        int idx = static_cast<int>(g.arcs.size());
        g.arcs.push_back({u, v, g.vertices[u].firstout, g.vertices[v].firstin, w});
        g.vertices[u].firstout = idx;
        g.vertices[v].firstin = idx;
    }
    return g;
}

vector<int> matrixNeighbors(const MatrixGraph& g, int u) {
    vector<int> result;
    for (int v = 0; v < static_cast<int>(g.vertices.size()); ++v) {
        if (u != v && g.matrix[u][v] < INF / 2) result.push_back(v);
    }
    return result;
}

vector<int> listNeighbors(const ListGraph& g, int u) {
    vector<int> result;
    for (const auto& item : g.adj[u]) result.push_back(item.first);
    return result;
}

vector<int> multiListNeighbors(const MultiListGraph& g, int u) {
    vector<int> result;
    for (int e = g.vertices[u].firstedge; e != -1;) {
        const auto& box = g.edges[e];
        int v = (box.ivex == u) ? box.jvex : box.ivex;
        result.push_back(v);
        e = (box.ivex == u) ? box.ilink : box.jlink;
    }
    return result;
}

vector<int> orthogonalNeighbors(const OrthogonalGraph& g, int u) {
    vector<int> result;
    for (int a = g.vertices[u].firstout; a != -1; a = g.arcs[a].tlink) {
        result.push_back(g.arcs[a].headvex);
    }
    return result;
}

vector<int> dfsIterative(int start, int n, vector<int> (*getter)(int, const void*), const void* gptr) {
    vector<int> order;
    vector<bool> visited(n, false);
    vector<int> st;
    st.push_back(start);
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        if (visited[u]) continue;
        visited[u] = true;
        order.push_back(u);
        vector<int> neighbors = getter(u, gptr);
        sort(neighbors.begin(), neighbors.end(), greater<int>());
        for (int v : neighbors) {
            if (!visited[v]) st.push_back(v);
        }
    }
    return order;
}

vector<int> bfsIterative(int start, int n, vector<int> (*getter)(int, const void*), const void* gptr) {
    vector<int> order;
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        vector<int> neighbors = getter(u, gptr);
        sort(neighbors.begin(), neighbors.end());
        for (int v : neighbors) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return order;
}

vector<int> matrixGetterAdapter(int u, const void* gptr) {
    return matrixNeighbors(*static_cast<const MatrixGraph*>(gptr), u);
}

vector<int> listGetterAdapter(int u, const void* gptr) {
    return listNeighbors(*static_cast<const ListGraph*>(gptr), u);
}

vector<int> multiGetterAdapter(int u, const void* gptr) {
    return multiListNeighbors(*static_cast<const MultiListGraph*>(gptr), u);
}

vector<int> orthogonalGetterAdapter(int u, const void* gptr) {
    return orthogonalNeighbors(*static_cast<const OrthogonalGraph*>(gptr), u);
}

void printApplicability() {
    subtitle("图片中的适用性总表");
    cout << left << setw(18) << "图的类型"
         << setw(18) << "邻接矩阵"
         << setw(18) << "邻接表"
         << setw(18) << "邻接多重表"
         << setw(18) << "十字链表" << '\n';
    cout << string(90, '-') << '\n';
    cout << left << setw(18) << "有向图" << setw(18) << "√" << setw(18) << "√" << setw(18) << "×" << setw(18) << "√" << '\n';
    cout << left << setw(18) << "无向图" << setw(18) << "√" << setw(18) << "√" << setw(18) << "√" << setw(18) << "×" << '\n';
}

void printMatrix(const MatrixGraph& g, const string& title) {
    subtitle(title + (g.directed ? "（有向图）" : "（无向图）"));
    cout << setw(6) << " ";
    for (char c : g.vertices) cout << setw(6) << c;
    cout << '\n';
    for (size_t i = 0; i < g.matrix.size(); ++i) {
        cout << setw(6) << g.vertices[i];
        for (size_t j = 0; j < g.matrix[i].size(); ++j) {
            if (g.matrix[i][j] >= INF / 2) cout << setw(6) << "∞";
            else cout << setw(6) << g.matrix[i][j];
        }
        cout << '\n';
    }
}

void printList(const ListGraph& g, const string& title) {
    subtitle(title + (g.directed ? "（有向图）" : "（无向图）"));
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << g.vertices[i] << " -> ";
        if (g.adj[i].empty()) {
            cout << "∅";
        } else {
            for (size_t k = 0; k < g.adj[i].size(); ++k) {
                cout << g.vertices[g.adj[i][k].first] << '(' << g.adj[i][k].second << ')';
                if (k + 1 != g.adj[i].size()) cout << " -> ";
            }
        }
        cout << '\n';
    }
}

void printMultiList(const MultiListGraph& g, const string& title) {
    subtitle(title + "（无向图）");
    cout << "顶点表：\n";
    cout << left << setw(8) << "序号" << setw(8) << "顶点" << setw(10) << "firstedge" << '\n';
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << left << setw(8) << i << setw(8) << g.vertices[i].data << setw(10) << emptyText(g.vertices[i].firstedge) << '\n';
    }
    cout << "边表：\n";
    cout << left << setw(8) << "序号" << setw(10) << "边" << setw(10) << "权值" << setw(10) << "ilink" << setw(10) << "jlink" << '\n';
    for (size_t i = 0; i < g.edges.size(); ++i) {
        const auto& e = g.edges[i];
        cout << left << setw(8) << i
             << setw(10) << edgeNameUndirected(g.vertices[e.ivex].data, g.vertices[e.jvex].data)
             << setw(10) << e.weight << setw(10) << emptyText(e.ilink) << setw(10) << emptyText(e.jlink) << '\n';
    }
}

void printOrthogonal(const OrthogonalGraph& g, const string& title) {
    subtitle(title + "（有向图）");
    cout << "顶点表：\n";
    cout << left << setw(8) << "序号" << setw(8) << "顶点" << setw(10) << "firstout" << setw(10) << "firstin" << '\n';
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << left << setw(8) << i << setw(8) << g.vertices[i].data << setw(10) << emptyText(g.vertices[i].firstout) << setw(10) << emptyText(g.vertices[i].firstin) << '\n';
    }
    cout << "弧表：\n";
    cout << left << setw(8) << "序号" << setw(10) << "弧" << setw(10) << "权值" << setw(10) << "tlink" << setw(10) << "hlink" << '\n';
    for (size_t i = 0; i < g.arcs.size(); ++i) {
        const auto& a = g.arcs[i];
        cout << left << setw(8) << i
             << setw(10) << edgeNameDirected(g.vertices[a.tailvex].data, g.vertices[a.headvex].data)
             << setw(10) << a.weight << setw(10) << emptyText(a.tlink) << setw(10) << emptyText(a.hlink) << '\n';
    }
}

void printTraversalResult(const vector<char>& vertices, const string& title, const vector<int>& dfs, const vector<int>& bfs) {
    subtitle(title);
    cout << "DFS 访问序列：" << pathText(vertices, dfs) << '\n';
    cout << "BFS 访问序列：" << pathText(vertices, bfs) << '\n';
}

} // namespace

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    vector<char> undirectedVertices = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<tuple<int, int, int>> undirectedEdges = {
        {0, 1, 1}, {0, 2, 2}, {1, 3, 3}, {1, 4, 4}, {2, 5, 5}, {4, 5, 6}
    };

    vector<char> directedVertices = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<tuple<int, int, int>> directedEdges = {
        {0, 1, 1}, {0, 2, 1}, {1, 3, 1}, {2, 3, 1}, {3, 4, 1}, {4, 5, 1}, {5, 2, 1}
    };

    MatrixGraph undirectedMatrix = buildMatrixGraph(undirectedVertices, undirectedEdges, false);
    ListGraph undirectedList = buildListGraph(undirectedVertices, undirectedEdges, false);
    MultiListGraph multiList = buildMultiListGraph(undirectedVertices, undirectedEdges);

    MatrixGraph directedMatrix = buildMatrixGraph(directedVertices, directedEdges, true);
    ListGraph directedList = buildListGraph(directedVertices, directedEdges, true);
    OrthogonalGraph orthogonal = buildOrthogonalGraph(directedVertices, directedEdges);

    banner("图的结构与遍历学习程序");
    cout << "本程序覆盖：邻接矩阵、邻接表、邻接多重表、十字链表，以及 DFS / BFS 遍历。\n";
    cout << "所有注释与输出均使用中文，适合和课本图片一起学习。\n";

    printApplicability();

    banner("一、无向图示例：邻接矩阵 + 邻接表 + 邻接多重表");
    printMatrix(undirectedMatrix, "无向图的邻接矩阵");
    printList(undirectedList, "无向图的邻接表");
    printMultiList(multiList, "无向图的邻接多重表");

    banner("二、有向图示例：邻接矩阵 + 邻接表 + 十字链表");
    printMatrix(directedMatrix, "有向图的邻接矩阵");
    printList(directedList, "有向图的邻接表");
    printOrthogonal(orthogonal, "有向图的十字链表");

    banner("三、遍历演示：只要能枚举邻接点，四种存储结构都能支持 DFS / BFS");
    cout << "这里统一从顶点 A 开始，演示不同结构下的遍历接口。\n";

    vector<int> umDfs = dfsIterative(0, static_cast<int>(undirectedVertices.size()), matrixGetterAdapter, &undirectedMatrix);
    vector<int> umBfs = bfsIterative(0, static_cast<int>(undirectedVertices.size()), matrixGetterAdapter, &undirectedMatrix);
    printTraversalResult(undirectedVertices, "无向图 - 邻接矩阵遍历结果", umDfs, umBfs);

    vector<int> ulDfs = dfsIterative(0, static_cast<int>(undirectedVertices.size()), listGetterAdapter, &undirectedList);
    vector<int> ulBfs = bfsIterative(0, static_cast<int>(undirectedVertices.size()), listGetterAdapter, &undirectedList);
    printTraversalResult(undirectedVertices, "无向图 - 邻接表遍历结果", ulDfs, ulBfs);

    vector<int> mlDfs = dfsIterative(0, static_cast<int>(undirectedVertices.size()), multiGetterAdapter, &multiList);
    vector<int> mlBfs = bfsIterative(0, static_cast<int>(undirectedVertices.size()), multiGetterAdapter, &multiList);
    printTraversalResult(undirectedVertices, "无向图 - 邻接多重表遍历结果", mlDfs, mlBfs);

    vector<int> dmDfs = dfsIterative(0, static_cast<int>(directedVertices.size()), matrixGetterAdapter, &directedMatrix);
    vector<int> dmBfs = bfsIterative(0, static_cast<int>(directedVertices.size()), matrixGetterAdapter, &directedMatrix);
    printTraversalResult(directedVertices, "有向图 - 邻接矩阵遍历结果", dmDfs, dmBfs);

    vector<int> dlDfs = dfsIterative(0, static_cast<int>(directedVertices.size()), listGetterAdapter, &directedList);
    vector<int> dlBfs = bfsIterative(0, static_cast<int>(directedVertices.size()), listGetterAdapter, &directedList);
    printTraversalResult(directedVertices, "有向图 - 邻接表遍历结果", dlDfs, dlBfs);

    vector<int> oDfs = dfsIterative(0, static_cast<int>(directedVertices.size()), orthogonalGetterAdapter, &orthogonal);
    vector<int> oBfs = bfsIterative(0, static_cast<int>(directedVertices.size()), orthogonalGetterAdapter, &orthogonal);
    printTraversalResult(directedVertices, "有向图 - 十字链表遍历结果", oDfs, oBfs);

    banner("四、学习建议");
    cout << "1. 邻接矩阵：适合判断边是否存在，空间开销与顶点数平方成正比。\n";
    cout << "2. 邻接表：适合稀疏图，遍历邻接点更高效。\n";
    cout << "3. 邻接多重表：专门服务无向图，一条边只存一份，但能同时连接两个顶点。\n";
    cout << "4. 十字链表：专门服务有向图，既能顺着出边找，也能沿入边回溯。\n";
    cout << "5. DFS 与 BFS 的核心不是具体存储结构，而是“能否快速枚举邻接点”。\n";
    cout << "6. 这也是为什么图片中邻接矩阵、邻接表、邻接多重表、十字链表各有适用场景。\n";

    cout << "\n程序执行完毕。你可以配合 HTML 动画页面逐步学习。\n";
    return 0;
}



