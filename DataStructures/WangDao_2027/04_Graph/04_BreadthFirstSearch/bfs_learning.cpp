#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

/*
  bfs_learning.cpp
  用途: 学习图的广度优先搜索(BFS)的示例程序。

  本文件包含：
    1) 邻接矩阵表示的图（Adjacency Matrix）
       - BFS 遍历（使用队列）
    2) 邻接表表示的图（Adjacency List）
       - BFS 遍历（使用队列）
    3) 记录访问顺序、父节点与距离（distance）
    4) 示例图与自动演示（程序运行时会输出详细过程）

  注释与输出均为中文，用于学习和教学。
*/

void printDivider() {
    cout << "------------------------------------------------------------\n";
}

// ---------- 邻接矩阵表示的图 ----------
struct GraphMatrix {
    int n; // 节点数，编号为 0 到 n-1
    vector<vector<int>> mat; // n x n 的邻接矩阵，0/1 表示是否有边

    GraphMatrix(int n = 0) : n(n), mat(n, vector<int>(n, 0)) {}

    void addEdge(int u, int v, bool undirected = true) {
        if (u < 0 || u >= n || v < 0 || v >= n) return;
        mat[u][v] = 1;
        if (undirected) mat[v][u] = 1;
    }

    // 从 start 开始执行 BFS，并逐步输出中文过程。
    // 这个版本可以处理非连通图：每个未访问连通分量都单独开始 BFS。
    void bfs(int start = 0) {
        vector<int> visited(n, 0);   // 0 未访问，1 已访问
        vector<int> parent(n, -1);   // 父节点，用于恢复路径
        vector<int> dist(n, -1);      // 距离：起点到当前点的最短距离
        vector<int> order;            // 访问顺序

        cout << "开始矩阵-BFS，从节点 " << start << " 开始\n";

        // 注意：为了“更完整”地演示非连通图，这里在外层循环中检查所有未访问节点。
        // 若图是连通图，则它只会进入一次。
        for (int s = 0; s < n; ++s) {
            if (visited[s]) continue;

            cout << "矩阵-BFS: 发现新的连通分量，起点为 " << s << "\n";
            queue<int> q;
            q.push(s);
            visited[s] = 1;
            parent[s] = -1;
            dist[s] = 0;
            order.push_back(s);
            cout << "  矩阵-BFS: 访问节点 " << s << "，距离=0，入队\n";

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                cout << "矩阵-BFS: 出队节点 " << u << "，当前距离 = " << dist[u] << "\n";

                // 关键：BFS 的“扩展顺序”是按层次遍历；
                // 所有与 u 相邻且未访问的点都会被加入队列，且它们的 dist 都是 dist[u] + 1。
                for (int v = 0; v < n; ++v) {
                    if (mat[u][v] == 0) continue;
                    if (!visited[v]) {
                        visited[v] = 1;
                        parent[v] = u;
                        dist[v] = dist[u] + 1;
                        order.push_back(v);
                        q.push(v);
                        cout << "  矩阵-BFS: 发现邻居 " << v << "，父节点=" << u
                             << "，距离=" << dist[v] << "，入队\n";
                    } else {
                        // 这条边很可能是已访问过的邻居，BFS 里不需要重复访问；
                        // 但输出它可以帮助理解图的连接关系。
                        cout << "  矩阵-BFS: 邻居 " << v << " 已访问，跳过（防止重复入队）\n";
                    }
                }
            }
        }

        printDivider();
        cout << "矩阵-BFS 完成。访问顺序：";
        for (int u : order) cout << u << " ";
        cout << "\n父节点数组(parent)：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << parent[i] << "\n";
        cout << "距离数组(dist)：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << dist[i] << "\n";
    }
};

// ---------- 邻接表表示的图 ----------
struct GraphList {
    int n;
    vector<vector<int>> adj; // 邻接表：adj[u] 存放 u 的所有邻居

    GraphList(int n = 0) : n(n), adj(n) {}

    void addEdge(int u, int v, bool undirected = true) {
        if (u < 0 || u >= n || v < 0 || v >= n) return;
        adj[u].push_back(v);
        if (undirected) adj[v].push_back(u);
    }

    void bfs(int start = 0) {
        vector<int> visited(n, 0);
        vector<int> parent(n, -1);
        vector<int> dist(n, -1);
        vector<int> order;

        cout << "开始表-BFS，从节点 " << start << " 开始\n";

        // 处理所有未访问连通分量.
        for (int s = 0; s < n; ++s) {
            if (visited[s]) continue;

            cout << "表-BFS: 发现新的连通分量，起点为 " << s << "\n";
            queue<int> q;
            q.push(s);
            visited[s] = 1;
            parent[s] = -1;
            dist[s] = 0;
            order.push_back(s);
            cout << "  表-BFS: 访问节点 " << s << "，距离=0，入队\n";

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                cout << "表-BFS: 出队节点 " << u << "，当前距离 = " << dist[u] << "\n";

                // 由于邻接表中是直接枚举 u 的邻居，因此遍历方式非常自然。
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = 1;
                        parent[v] = u;
                        dist[v] = dist[u] + 1;
                        order.push_back(v);
                        q.push(v);
                        cout << "  表-BFS: 发现邻居 " << v << "，父节点=" << u
                             << "，距离=" << dist[v] << "，入队\n";
                    } else {
                        cout << "  表-BFS: 邻居 " << v << " 已访问，直接忽略\n";
                    }
                }
            }
        }

        printDivider();
        cout << "表-BFS 完成。访问顺序：";
        for (int u : order) cout << u << " ";
        cout << "\n父节点数组(parent)：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << parent[i] << "\n";
        cout << "距离数组(dist)：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << dist[i] << "\n";
    }
};

// ---------- 生成示例图 ----------
void buildSampleGraph(GraphMatrix &gm, GraphList &gl) {
    // 一个无向图，节点编号：0..6
    // 边集合：
    // 0-1, 0-2, 1-3, 1-4, 2-5, 3-4, 5-6
    // 说明：
    // - 这是一个典型的“层次连接”图，适合观察 BFS 的层序访问。
    // - 从 0 出发，访问顺序大致是 0 -> 1,2 -> 3,4,5 -> 6
    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2},
        {1, 3}, {1, 4},
        {2, 5},
        {3, 4},
        {5, 6}
    };

    for (auto &edge : edges) {
        gm.addEdge(edge.first, edge.second, true);
        gl.addEdge(edge.first, edge.second, true);
    }
}

// ---------- 主程序 ----------
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "图的广度优先搜索(BFS) 学习示例程序\n";
    printDivider();
    cout << "程序说明（中文）:\n";
    cout << "  - 演示邻接矩阵与邻接表两种图表示的 BFS。\n";
    cout << "  - 我们使用队列（queue）来模拟 BFS 的层次遍历过程。\n";
    cout << "  - 程序会输出访问顺序、父节点、距离以及每一步入队/出队信息。\n";
    printDivider();

    int n = 7;
    GraphMatrix gm(n);
    GraphList gl(n);
    buildSampleGraph(gm, gl);

    cout << "示例图：共 " << n << " 个节点，编号为 0.." << n - 1 << "。\n";
    cout << "边集合：0-1, 0-2, 1-3, 1-4, 2-5, 3-4, 5-6\n";
    printDivider();

    cout << "第一部分：邻接矩阵表示的 BFS\n";
    gm.bfs(0);

    printDivider();
    cout << "第二部分：邻接表表示的 BFS\n";
    gl.bfs(0);

    printDivider();
    cout << "学习总结：\n";
    cout << "  1. BFS 的核心思想是“按层扩展”，因此需要使用队列。\n";
    cout << "  2. 无论是邻接矩阵还是邻接表，只要能枚举某点的所有邻接点，BFS 就能工作。\n";
    cout << "  3. BFS 的典型应用包括：求最短路、无权图最短路径、层次遍历、连通块统计等。\n";
    cout << "  4. 访问顺序是“先广后深”的思想，每次先访问当前层的所有点，再扩展下一层。\n";
    printDivider();
    cout << "演示结束。\n";
    cout << "提示：如果想学习不同的图，您可以修改 buildSampleGraph() 中的边集合，或者改成从标准输入读入图。\n";
    return 0;
}
