// minimum_spanning_tree_learning.cpp
// 学习最小生成树（Minimum Spanning Tree, MST）
// 包含：Prim 算法与 Kruskal 算法
// 每种算法都提供邻接矩阵和邻接表两种数据结构实现
// 注释与输出均为中文，便于学习和课堂讲解

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>
#include <iomanip>
#include <limits>
#include <functional>

using namespace std;
using ll = long long;
const ll INF = (1LL << 60);

// =====================================================
// 并查集（Union-Find）
// =====================================================
struct DisjointSet {
    vector<int> parent;
    vector<int> rank;

    explicit DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) ++rank[a];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

// =====================================================
// 边结构：用于 Kruskal 统计
// =====================================================
struct Edge {
    ll weight;
    int u;
    int v;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// =====================================================
// 1）邻接矩阵表示的图
// =====================================================
struct GraphMatrix {
    int n;
    vector<vector<ll>> mat;
    bool directed;

    GraphMatrix(int n = 0, bool directed = false)
        : n(n), directed(directed) {
        mat.assign(n, vector<ll>(n, INF));
        for (int i = 0; i < n; ++i) mat[i][i] = 0;
    }

    void addEdge(int u, int v, ll w) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "[错误] 顶点编号越界，无法加入边 " << u << " -> " << v << "\n";
            return;
        }
        mat[u][v] = w;
        if (!directed) mat[v][u] = w;
    }

    void printMatrix() const {
        cout << "\n[邻接矩阵] 当前图：\n";
        cout << "    ";
        for (int i = 0; i < n; ++i) cout << setw(4) << i;
        cout << "\n";
        for (int i = 0; i < n; ++i) {
            cout << setw(4) << i << " ";
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == INF) cout << setw(4) << "INF";
                else cout << setw(4) << mat[i][j];
            }
            cout << "\n";
        }
    }

    // Prim 算法（邻接矩阵版本）
    void primMatrix() {
        cout << "\n=====================================================\n";
        cout << "[邻接矩阵版 Prim 算法]\n";
        cout << "核心思想：每次从已在 MST 集合中的顶点出发，选择最小连接代价的边，加入新顶点。\n";
        cout << "=====================================================\n";

        vector<ll> lowcost(n, INF);
        vector<int> parent(n, -1);
        vector<bool> used(n, false);
        ll totalWeight = 0;

        // 从顶点 0 开始构造 MST
        lowcost[0] = 0;
        parent[0] = -1;
        cout << "初始：将顶点 0 作为起点，lowcost[0] = 0\n";

        for (int i = 0; i < n; ++i) {
            int u = -1;
            for (int v = 0; v < n; ++v) {
                if (!used[v] && (u == -1 || lowcost[v] < lowcost[u])) {
                    u = v;
                }
            }

            if (u == -1) break;
            used[u] = true;
            cout << "选中顶点 " << u << "，加入 MST";
            if (parent[u] != -1) {
                cout << "，连接边：" << parent[u] << " -> " << u << "，权重 = " << lowcost[u];
                totalWeight += lowcost[u];
            } else {
                cout << "（起点）";
            }
            cout << "\n";

            for (int v = 0; v < n; ++v) {
                if (!used[v] && mat[u][v] != INF && mat[u][v] < lowcost[v]) {
                    lowcost[v] = mat[u][v];
                    parent[v] = u;
                    cout << "  更新：lowcost[" << v << "] = " << lowcost[v]
                         << "，由顶点 " << u << " 连接\n";
                }
            }
        }

        cout << "\nPrim（矩阵版）最终最小生成树总权重 = " << totalWeight << "\n";
        cout << "MST 边集：\n";
        for (int v = 1; v < n; ++v) {
            if (parent[v] != -1) {
                cout << "  " << parent[v] << " -- " << v << " (权重 " << mat[parent[v]][v] << ")\n";
            }
        }
    }

    // Kruskal 算法（邻接矩阵版本）
    void kruskalMatrix() {
        cout << "\n=====================================================\n";
        cout << "[邻接矩阵版 Kruskal 算法]\n";
        cout << "核心思想：按权值从小到大依次考察边，若两端点不在同一集合，就加入 MST。\n";
        cout << "=====================================================\n";

        vector<Edge> edges;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (mat[i][j] != INF && mat[i][j] != 0) {
                    edges.push_back({mat[i][j], i, j});
                }
            }
        }

        sort(edges.begin(), edges.end());
        cout << "所有候选边已按权值排序：\n";
        for (const auto& e : edges) {
            cout << "  边 " << e.u << " -- " << e.v << "，权重 = " << e.weight << "\n";
        }

        DisjointSet ds(n);
        vector<Edge> mst;
        ll totalWeight = 0;

        for (const auto& e : edges) {
            if (ds.same(e.u, e.v)) {
                cout << "  跳过边 " << e.u << " -- " << e.v << "：两点已经在同一集合\n";
                continue;
            }
            ds.unite(e.u, e.v);
            mst.push_back(e);
            totalWeight += e.weight;
            cout << "  选中边 " << e.u << " -- " << e.v << "，权重 = " << e.weight << "，加入 MST\n";
            if ((int)mst.size() == n - 1) break;
        }

        cout << "\nKruskal（矩阵版）最终最小生成树总权重 = " << totalWeight << "\n";
        cout << "MST 边集：\n";
        for (const auto& e : mst) {
            cout << "  " << e.u << " -- " << e.v << " (权重 " << e.weight << ")\n";
        }
    }
};

// =====================================================
// 2）邻接表表示的图
// =====================================================
struct GraphList {
    int n;
    vector<vector<pair<int, ll>>> adj;
    bool directed;

    GraphList(int n = 0, bool directed = false)
        : n(n), directed(directed) {
        adj.assign(n, {});
    }

    void addEdge(int u, int v, ll w) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "[错误] 顶点编号越界，无法加入边 " << u << " -> " << v << "\n";
            return;
        }
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
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
                auto [v, w] = adj[i][j];
                cout << "(" << v << ", " << w << ")";
                if (j + 1 < adj[i].size()) cout << " -> ";
            }
            cout << "\n";
        }
    }

    // Prim 算法（邻接表版本）
    void primList() {
        cout << "\n=====================================================\n";
        cout << "[邻接表版 Prim 算法]\n";
        cout << "与矩阵版相同的思路：维护 lowcost 和 parent 数组。\n";
        cout << "=====================================================\n";

        vector<ll> lowcost(n, INF);
        vector<int> parent(n, -1);
        vector<bool> used(n, false);
        ll totalWeight = 0;

        lowcost[0] = 0;
        parent[0] = -1;
        cout << "初始：从顶点 0 开始，低连接代价 lowcost[0] = 0\n";

        for (int i = 0; i < n; ++i) {
            int u = -1;
            for (int v = 0; v < n; ++v) {
                if (!used[v] && (u == -1 || lowcost[v] < lowcost[u])) {
                    u = v;
                }
            }

            if (u == -1) break;
            used[u] = true;
            cout << "选中顶点 " << u << "，加入 MST";
            if (parent[u] != -1) {
                cout << "，连接边：" << parent[u] << " -> " << u << "，权重 = " << lowcost[u];
                totalWeight += lowcost[u];
            } else {
                cout << "（起点）";
            }
            cout << "\n";

            for (auto [v, w] : adj[u]) {
                if (!used[v] && w < lowcost[v]) {
                    lowcost[v] = w;
                    parent[v] = u;
                    cout << "  更新：lowcost[" << v << "] = " << lowcost[v]
                         << "，由顶点 " << u << " 连接\n";
                }
            }
        }

        cout << "\nPrim（邻接表版）最终最小生成树总权重 = " << totalWeight << "\n";
        cout << "MST 边集：\n";
        for (int v = 1; v < n; ++v) {
            if (parent[v] != -1) {
                // 在邻接表表示中，找出一条父节点到当前顶点的实际边权重
                ll edgeW = INF;
                for (auto [to, w] : adj[parent[v]]) {
                    if (to == v) {
                        edgeW = w;
                        break;
                    }
                }
                if (edgeW != INF) {
                    cout << "  " << parent[v] << " -- " << v << " (权重 " << edgeW << ")\n";
                }
            }
        }
    }

    // Kruskal 算法（邻接表版本）
    void kruskalList() {
        cout << "\n=====================================================\n";
        cout << "[邻接表版 Kruskal 算法]\n";
        cout << "先把所有无向边整理成边集合，再按边权升序处理。\n";
        cout << "=====================================================\n";

        vector<Edge> edges;
        for (int u = 0; u < n; ++u) {
            for (auto [v, w] : adj[u]) {
                if (u < v) {
                    edges.push_back({w, u, v});
                }
            }
        }

        sort(edges.begin(), edges.end());
        cout << "所有候选边已按权值排序：\n";
        for (const auto& e : edges) {
            cout << "  边 " << e.u << " -- " << e.v << "，权重 = " << e.weight << "\n";
        }

        DisjointSet ds(n);
        vector<Edge> mst;
        ll totalWeight = 0;

        for (const auto& e : edges) {
            if (ds.same(e.u, e.v)) {
                cout << "  跳过边 " << e.u << " -- " << e.v << "：两点已经在同一集合\n";
                continue;
            }
            ds.unite(e.u, e.v);
            mst.push_back(e);
            totalWeight += e.weight;
            cout << "  选中边 " << e.u << " -- " << e.v << "，权重 = " << e.weight << "，加入 MST\n";
            if ((int)mst.size() == n - 1) break;
        }

        cout << "\nKruskal（邻接表版）最终最小生成树总权重 = " << totalWeight << "\n";
        cout << "MST 边集：\n";
        for (const auto& e : mst) {
            cout << "  " << e.u << " -- " << e.v << " (权重 " << e.weight << ")\n";
        }
    }
};

// =====================================================
// 主函数：构造示例图并依次演示
// =====================================================
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    cout << "=====================================================\n";
    cout << "最小生成树（Minimum Spanning Tree）学习示例\n";
    cout << "本程序说明：\n";
    cout << "  1. Prim 算法：适合邻接矩阵/密集图，可在 O(n^2) 中完成\n";
    cout << "  2. Kruskal 算法：适合邻接表/稀疏图，核心是排序 + 并查集\n";
    cout << "  3. 两种数据结构：邻接矩阵与邻接表都给出实现\n";
    cout << "=====================================================\n";

    // 示例图：6 个顶点，连通无向带权图
    // 具体边：
    // 0-1 4
    // 0-2 6
    // 0-3 1
    // 1-2 2
    // 1-4 5
    // 2-3 3
    // 2-4 4
    // 3-4 2
    // 3-5 5
    // 4-5 1
    // 最小生成树的总权值为 9（0-3, 3-2, 2-1, 3-4, 4-5）

    int n = 6;

    GraphMatrix gm(n, false);
    gm.addEdge(0, 1, 4);
    gm.addEdge(0, 2, 6);
    gm.addEdge(0, 3, 1);
    gm.addEdge(1, 2, 2);
    gm.addEdge(1, 4, 5);
    gm.addEdge(2, 3, 3);
    gm.addEdge(2, 4, 4);
    gm.addEdge(3, 4, 2);
    gm.addEdge(3, 5, 5);
    gm.addEdge(4, 5, 1);

    gm.printMatrix();
    gm.primMatrix();
    gm.kruskalMatrix();

    GraphList gl(n, false);
    gl.addEdge(0, 1, 4);
    gl.addEdge(0, 2, 6);
    gl.addEdge(0, 3, 1);
    gl.addEdge(1, 2, 2);
    gl.addEdge(1, 4, 5);
    gl.addEdge(2, 3, 3);
    gl.addEdge(2, 4, 4);
    gl.addEdge(3, 4, 2);
    gl.addEdge(3, 5, 5);
    gl.addEdge(4, 5, 1);

    gl.printAdjList();
    gl.primList();
    gl.kruskalList();

    cout << "\n=====================================================\n";
    cout << "总结：\n";
    cout << "  - Prim 更适合密集图/邻接矩阵：时间复杂度接近 O(n^2)\n";
    cout << "  - Kruskal 更适合稀疏图/邻接表：时间复杂度约 O(E log E)\n";
    cout << "  - 这两个算法都能求出最小生成树（MST），但实现思路不同\n";
    cout << "=====================================================\n";

    return 0;
}

