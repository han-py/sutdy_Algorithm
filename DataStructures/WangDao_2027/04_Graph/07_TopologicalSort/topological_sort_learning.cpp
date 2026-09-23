// topological_sort_learning.cpp
// 学习拓扑排序（Topological Sort）
// 包含：邻接矩阵和邻接表两种数据结构
// 主要算法：Kahn 算法（入度法）
// 额外提供：基于 DFS 的拓扑排序（邻接表版），便于比较理解
// 注释与输出均为中文，适合学习和课堂讲解

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <string>

using namespace std;

// =====================================================
// 辅助：打印拓扑序列
// =====================================================
void print_order(const vector<int>& order) {
    for (size_t i = 0; i < order.size(); ++i) {
        if (i) cout << " -> ";
        cout << order[i];
    }
    cout << '\n';
}

// =====================================================
// 邻接矩阵：适合展示“图”和“入度”的变化
// 说明：这里图是有向图，mat[u][v] = 1 表示 u -> v
// =====================================================
struct GraphMatrix {
    int n;
    vector<vector<int>> mat;

    explicit GraphMatrix(int n = 0) : n(n), mat(n, vector<int>(n, 0)) {}

    void addEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "[错误] 顶点编号越界，无法加入边 " << u << " -> " << v << '\n';
            return;
        }
        mat[u][v] = 1;
    }

    void printMatrix() const {
        cout << "\n[邻接矩阵] 当前图：\n";
        cout << "    ";
        for (int i = 0; i < n; ++i) cout << setw(3) << i;
        cout << '\n';
        for (int i = 0; i < n; ++i) {
            cout << setw(3) << i << " ";
            for (int j = 0; j < n; ++j) {
                cout << setw(3) << mat[i][j];
            }
            cout << '\n';
        }
    }

    // Kahn 算法：邻接矩阵版
    vector<int> topoSortKahn() const {
        cout << "\n=====================================================\n";
        cout << "[邻接矩阵版] 拓扑排序（Kahn 算法 / 入度法）\n";
        cout << "核心思想：不断取出当前入度为 0 的顶点，并删除它的出边。\n";
        cout << "=====================================================\n";

        vector<int> indegree(n, 0);
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (mat[u][v]) ++indegree[v];
            }
        }

        cout << "初始入度数组：\n";
        for (int i = 0; i < n; ++i) {
            cout << "  顶点 " << i << " 的入度 = " << indegree[i] << '\n';
        }

        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
                cout << "  入队：顶点 " << i << "（初始入度为 0）\n";
            }
        }

        vector<int> order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            cout << "取出顶点 " << u << "，加入拓扑序\n";

            for (int v = 0; v < n; ++v) {
                if (mat[u][v]) {
                    --indegree[v];
                    cout << "  删除边 " << u << " -> " << v << "，顶点 " << v << " 的入度变为 " << indegree[v] << '\n';
                    if (indegree[v] == 0) {
                        q.push(v);
                        cout << "  顶点 " << v << " 入度变为 0，入队\n";
                    }
                }
            }
        }

        if ((int)order.size() != n) {
            cout << "\n检测到图中存在环，无法完成拓扑排序！\n";
            return {};
        }

        cout << "\n拓扑序结果：\n  ";
        print_order(order);
        return order;
    }
};

// =====================================================
// 邻接表：更适合稀疏图，拓扑排序时遍历出边更自然
// =====================================================
struct GraphList {
    int n;
    vector<vector<int>> adj;

    explicit GraphList(int n = 0) : n(n), adj(n) {}

    void addEdge(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "[错误] 顶点编号越界，无法加入边 " << u << " -> " << v << '\n';
            return;
        }
        adj[u].push_back(v);
    }

    void printAdjList() const {
        cout << "\n[邻接表] 当前图：\n";
        for (int i = 0; i < n; ++i) {
            cout << "  顶点 " << i << "：";
            if (adj[i].empty()) {
                cout << "空\n";
                continue;
            }
            for (size_t j = 0; j < adj[i].size(); ++j) {
                cout << adj[i][j];
                if (j + 1 < adj[i].size()) cout << " -> ";
            }
            cout << '\n';
        }
    }

    // Kahn 算法：邻接表版
    vector<int> topoSortKahn() const {
        cout << "\n=====================================================\n";
        cout << "[邻接表版] 拓扑排序（Kahn 算法 / 入度法）\n";
        cout << "核心思想：维护入度数组，反复取出入度为 0 的顶点。\n";
        cout << "=====================================================\n";

        vector<int> indegree(n, 0);
        for (int u = 0; u < n; ++u) {
            for (int v : adj[u]) {
                ++indegree[v];
            }
        }

        cout << "初始入度数组：\n";
        for (int i = 0; i < n; ++i) {
            cout << "  顶点 " << i << " 的入度 = " << indegree[i] << '\n';
        }

        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
                cout << "  入队：顶点 " << i << "（初始入度为 0）\n";
            }
        }

        vector<int> order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            cout << "取出顶点 " << u << "，加入拓扑序\n";

            for (int v : adj[u]) {
                --indegree[v];
                cout << "  删除边 " << u << " -> " << v << "，顶点 " << v << " 的入度变为 " << indegree[v] << '\n';
                if (indegree[v] == 0) {
                    q.push(v);
                    cout << "  顶点 " << v << " 入度变为 0，入队\n";
                }
            }
        }

        if ((int)order.size() != n) {
            cout << "\n检测到图中存在环，无法完成拓扑排序！\n";
            return {};
        }

        cout << "\n拓扑序结果：\n  ";
        print_order(order);
        return order;
    }

    // DFS 版拓扑排序：后序入栈，最后逆序得到拓扑序
    vector<int> topoSortDFS() const {
        cout << "\n=====================================================\n";
        cout << "[邻接表版] 拓扑排序（DFS 后序法，拓展理解）\n";
        cout << "核心思想：对顶点做 DFS，在回溯时记录顺序，最后逆序输出。\n";
        cout << "=====================================================\n";

        vector<int> state(n, 0); // 0未访问，1访问中，2已完成
        vector<int> order;
        bool hasCycle = false;

        function<void(int)> dfs = [&](int u) {
            state[u] = 1;
            cout << "访问顶点 " << u << "\n";
            for (int v : adj[u]) {
                if (state[v] == 0) {
                    cout << "  继续访问未访问顶点 " << v << '\n';
                    dfs(v);
                    if (hasCycle) return;
                } else if (state[v] == 1) {
                    cout << "  发现返祖边 " << u << " -> " << v << "，说明图中存在环！\n";
                    hasCycle = true;
                    return;
                }
            }
            state[u] = 2;
            order.push_back(u);
            cout << "回溯完成，顶点 " << u << " 加入结果序列\n";
        };

        for (int i = 0; i < n && !hasCycle; ++i) {
            if (state[i] == 0) dfs(i);
        }

        if (hasCycle) {
            cout << "\n检测到图中存在环，无法完成拓扑排序！\n";
            return {};
        }

        reverse(order.begin(), order.end());
        cout << "\nDFS 拓扑序结果：\n  ";
        print_order(order);
        return order;
    }
};

// =====================================================
// 主函数：构造示例 DAG 并演示两种表示法和两种算法
// =====================================================
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    cout << "=====================================================\n";
    cout << "拓扑排序（Topological Sort）学习示例\n";
    cout << "本程序演示：\n";
    cout << "  1. 邻接矩阵版 Kahn 算法\n";
    cout << "  2. 邻接表版 Kahn 算法\n";
    cout << "  3. 邻接表版 DFS 拓扑排序（拓展理解）\n";
    cout << "=====================================================\n";

    // 示例 DAG（无环有向图）
    // 顶点：0..5
    // 边：
    // 0 -> 1, 0 -> 2
    // 1 -> 3
    // 2 -> 3, 2 -> 4
    // 3 -> 5
    // 4 -> 5
    // 一个合法拓扑序例如：0 1 2 3 4 5 或 0 2 1 4 3 5 等
    int n = 6;

    GraphMatrix gm(n);
    gm.addEdge(0, 1);
    gm.addEdge(0, 2);
    gm.addEdge(1, 3);
    gm.addEdge(2, 3);
    gm.addEdge(2, 4);
    gm.addEdge(3, 5);
    gm.addEdge(4, 5);

    gm.printMatrix();
    gm.topoSortKahn();

    GraphList gl(n);
    gl.addEdge(0, 1);
    gl.addEdge(0, 2);
    gl.addEdge(1, 3);
    gl.addEdge(2, 3);
    gl.addEdge(2, 4);
    gl.addEdge(3, 5);
    gl.addEdge(4, 5);

    gl.printAdjList();
    gl.topoSortKahn();
    gl.topoSortDFS();

    cout << "\n=====================================================\n";
    cout << "学习总结：\n";
    cout << "  - 如果图中存在环，就无法进行拓扑排序\n";
    cout << "  - Kahn 算法直观：依赖入度数组，适合讲解和工程实现\n";
    cout << "  - DFS 拓扑排序更适合从深度优先搜索的视角理解\n";
    cout << "  - 邻接矩阵适合展示图结构；邻接表更适合稀疏图\n";
    cout << "=====================================================\n";

    return 0;
}

