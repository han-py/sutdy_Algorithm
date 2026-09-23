// shortest_path_learning.cpp
// 学习最短路径：包含不带权（BFS）与带权（Dijkstra）两类算法
// 每类都提供邻接矩阵与邻接表的实现，注释与输出均为中文，便于教学
// 演示：程序会建立示例图并依次运行四种实现（无权-矩阵/表，带权(Dijkstra)-矩阵/表）
// 另外提供 Bellman-Ford（邻接表实现）以演示带负权边的情况

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <tuple>
#include <functional>
#include <utility>
#include <stack>
#include <iomanip>
#include <climits>

using namespace std;
using ll = long long;
const ll INF = (1LL<<60);

// 辅助：打印从 start 到 v 的路径（通过 parent 数组）
void print_path(const vector<int>& parent, int start, int v) {
    if (v == -1) {
        cout << "（不可达）";
        return;
    }
    vector<int> path;
    int cur = v;
    while (cur != -1) {
        path.push_back(cur);
        if (cur == start) break;
        cur = parent[cur];
    }
    if (path.empty() || path.back() != start) {
        cout << "（不可达）";
        return;
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << " -> ";
        cout << path[i];
    }
}

// =====================================================
// 邻接矩阵表示的图（支持带权和不带权）
// 节点编号假定为 0..n-1
// matrix[u][v] = weight（若不存在边则为 INF）或 0/1 用于无权图
// =====================================================
struct GraphMatrix {
    int n;
    vector<vector<ll>> mat; // 权重矩阵
    bool directed;

    GraphMatrix(int n=0, bool directed=false): n(n), directed(directed) {
        mat.assign(n, vector<ll>(n, INF));
        for (int i = 0; i < n; ++i) mat[i][i] = 0;
    }

    void addEdge(int u, int v, ll w=1) {
        mat[u][v] = w;
        if (!directed) mat[v][u] = w;
    }

    // 无权最短路径（使用 BFS）
    void unweightedShortestPathBFS(int start) {
        cout << "\n[邻接矩阵] 无权最短路径（BFS）从起点 " << start << " 开始\n";
        vector<int> dist(n, -1), parent(n, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        cout << "入队: " << start << " (距离=0)\n";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << "出队: " << u << " (距离=" << dist[u] << ")\n";
            for (int v = 0; v < n; ++v) {
                if (v==u) continue;
                // 在矩阵中，无权图把存在边表示为 1（或任何非INF且非0）
                if (mat[u][v] != INF && mat[u][v] != 0 && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                    cout << "  发现并入队: " << v << " (父=" << u << ", 距离=" << dist[v] << ")\n";
                }
            }
        }
        cout << "最终距离数组：\n";
        for (int i = 0; i < n; ++i) cout << " 节点 " << i << " : " << dist[i] << "\n";
        cout << "若需要路径示例，按节点输出从起点到该节点的路径：\n";
        for (int i = 0; i < n; ++i) {
            cout << "  路径 " << start << " -> " << i << " : ";
            if (dist[i] == -1) cout << "不可达";
            else print_path(parent, start, i);
            cout << "\n";
        }
    }

    // 带权最短路径（Dijkstra，矩阵实现，O(n^2)）
    void dijkstraMatrix(int start) {
        cout << "\n[邻接矩阵] 带权最短路径 Dijkstra（矩阵实现）起点=" << start << "\n";
        vector<ll> dist(n, INF);
        vector<int> parent(n, -1);
        vector<char> used(n, false);
        dist[start] = 0;
        for (int it = 0; it < n; ++it) {
            int v = -1;
            for (int i = 0; i < n; ++i) if (!used[i] && (v==-1 || dist[i] < dist[v])) v = i;
            if (v == -1 || dist[v] == INF) break;
            used[v] = true;
            cout << "选择最近未处理节点: " << v << " (dist=" << dist[v] << ")\n";
            for (int to = 0; to < n; ++to) {
                if (mat[v][to] != INF && mat[v][to] != 0) {
                    ll w = mat[v][to];
                    if (dist[v] + w < dist[to]) {
                        dist[to] = dist[v] + w;
                        parent[to] = v;
                        cout << "  松弛边 " << v << " -> " << to << " (权重=" << w << ")，更新 dist[" << to << "]=" << dist[to] << "，父=" << v << "\n";
                    }
                }
            }
        }
        cout << "最终距离（Dijkstra，矩阵）:\n";
        for (int i = 0; i < n; ++i) {
            cout << "  节点 " << i << " : ";
            if (dist[i] >= INF/4) cout << "INF";
            else cout << dist[i];
            cout << "\n";
        }
        cout << "路径举例：\n";
        for (int i = 0; i < n; ++i) {
            cout << "  " << start << " -> " << i << " : ";
            if (dist[i] >= INF/4) cout << "不可达";
            else print_path(parent, start, i);
            cout << "\n";
        }
    }
};

// =====================================================
// 邻接表表示的图（支持带权和不带权）
// =====================================================
struct GraphList {
    int n;
    vector<vector<int>> adj; // 无权图
    vector<vector<pair<int,ll>>> adjw; // 带权图
    bool directed;

    GraphList(int n=0, bool directed=false): n(n), directed(directed) {
        adj.assign(n, {});
        adjw.assign(n, {});
    }

    void addEdgeUnweighted(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    void addEdgeWeighted(int u, int v, ll w) {
        adjw[u].push_back({v,w});
        if (!directed) adjw[v].push_back({u,w});
    }

    // 无权最短路径（BFS，邻接表版）
    void unweightedShortestPathBFS(int start) {
        cout << "\n[邻接表] 无权最短路径（BFS）从起点 " << start << " 开始\n";
        vector<int> dist(n, -1), parent(n, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        cout << "入队: " << start << " (距离=0)\n";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << "出队: " << u << " (距离=" << dist[u] << ")\n";
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                    cout << "  发现并入队: " << v << " (父=" << u << ", 距离=" << dist[v] << ")\n";
                }
            }
        }
        cout << "最终距离数组：\n";
        for (int i = 0; i < n; ++i) cout << " 节点 " << i << " : " << dist[i] << "\n";
        cout << "路径示例：\n";
        for (int i = 0; i < n; ++i) {
            cout << "  路径 " << start << " -> " << i << " : ";
            if (dist[i] == -1) cout << "不可达";
            else print_path(parent, start, i);
            cout << "\n";
        }
    }

    // 带权最短路径（Dijkstra，邻接表 + 优先队列）
    void dijkstraList(int start) {
        cout << "\n[邻接表] 带权最短路径 Dijkstra（邻接表 + 优先队列） 起点=" << start << "\n";
        vector<ll> dist(n, INF);
        vector<int> parent(n, -1);
        dist[start] = 0;
        using pli = pair<ll,int>; // (dist, v)
        priority_queue<pli, vector<pli>, greater<pli>> pq;
        pq.push({0, start});
        cout << "将起点 " << start << " 加入优先队列（dist=0）\n";
        while (!pq.empty()) {
            auto [d,u] = pq.top(); pq.pop();
            if (d != dist[u]) continue; // 懒惰删除
            cout << "从队列取出节点 " << u << " (dist=" << d << ")\n";
            for (auto [v,w] : adjw[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                    cout << "  松弛边 " << u << " -> " << v << " (权重=" << w << ")，更新 dist[" << v << "]=" << dist[v] << "，入队\n";
                }
            }
        }
        cout << "最终距离（Dijkstra，邻接表）:\n";
        for (int i = 0; i < n; ++i) {
            cout << "  节点 " << i << " : ";
            if (dist[i] >= INF/4) cout << "INF";
            else cout << dist[i];
            cout << "\n";
        }
        cout << "路径举例：\n";
        for (int i = 0; i < n; ++i) {
            cout << "  " << start << " -> " << i << " : ";
            if (dist[i] >= INF/4) cout << "不可达";
            else print_path(parent, start, i);
            cout << "\n";
        }
    }

    // Bellman-Ford：邻接表实现，支持负权边（检测负环）
    // 返回 pair<hasNegativeCycle, dist_vector>
    pair<bool, vector<ll>> bellmanFord(int start) {
        cout << "\n[邻接表] Bellman-Ford（邻接表） 起点=" << start << "\n";
        vector<tuple<int,int,ll>> edges;
        for (int u = 0; u < n; ++u) {
            for (auto [v,w] : adjw[u]) edges.emplace_back(u,v,w);
        }
        vector<ll> dist(n, INF);
        vector<int> parent(n, -1);
        dist[start] = 0;
        cout << "开始进行最多 n-1 次松弛...\n";
        for (int i = 0; i < n-1; ++i) {
            bool any = false;
            cout << "  第 " << i+1 << " 轮松弛:\n";
            for (auto [u,v,w] : edges) {
                if (dist[u] < INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    any = true;
                    cout << "    松弛边 " << u << " -> " << v << " (w=" << w << ")，dist["<<v<<"]="<<dist[v]<<"\n";
                }
            }
            if (!any) { cout << "  无更多松弛，提前结束。\n"; break; }
        }
        // 检测负环
        cout << "检测是否存在负权回路...\n";
        for (auto [u,v,w] : edges) {
            if (dist[u] < INF && dist[u] + w < dist[v]) {
                cout << "检测到负权回路（edge "<<u<<"->"<<v<<" 可继续松弛）\n";
                return {true, dist};
            }
        }
        cout << "没有检测到负权回路。最终距离：\n";
        for (int i = 0; i < n; ++i) {
            cout << "  节点 " << i << " : ";
            if (dist[i] >= INF/4) cout << "INF";
            else cout << dist[i];
            cout << "\n";
        }
        return {false, dist};
    }
};

// =====================================================
// 示例与演示：构造若干简单图并演示四种/更多实现
// =====================================================
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << "最短路径学习示例（中文注释与输出）\n";
    cout << "演示内容：\n";
    cout << "  1) 无权最短路径（BFS）——邻接矩阵与邻接表实现\n";
    cout << "  2) 带权最短路径（Dijkstra）——邻接矩阵(O(n^2))与邻接表(优先队列)实现\n";
    cout << "  3) Bellman-Ford（邻接表）用于含负权边的情况并检测负环\n";

    // 示例 1：无权图（适用于 BFS）
    int n = 7;
    cout << "\n=== 示例 A：无权图（用于 BFS） ===\n";
    GraphMatrix gm(n, false);
    GraphList gl(n, false);
    // 添加无向无权边
    vector<pair<int,int>> edges = {
        {0,1},{0,2},{1,3},{2,3},{2,4},{3,5},{4,5},{5,6}
    };
    for (auto [u,v] : edges) {
        gm.addEdge(u,v,1);
        gl.addEdgeUnweighted(u,v);
    }
    int start = 0;
    gm.unweightedShortestPathBFS(start);
    gl.unweightedShortestPathBFS(start);

    // 示例 2：带权图（非负权，适用于 Dijkstra）
    cout << "\n=== 示例 B：带权图（非负权，Dijkstra 演示） ===\n";
    int n2 = 6;
    GraphMatrix gwm(n2, false);
    GraphList gwl(n2, false);
    // 无向带权示例
    vector<tuple<int,int,ll>> edges_w = {
        {0,1,7},{0,2,9},{0,5,14},{1,2,10},{1,3,15},{2,3,11},{2,5,2},{3,4,6},{4,5,9}
    };
    for (auto [u,v,w] : edges_w) {
        gwm.addEdge(u,v,w);
        gwl.addEdgeWeighted(u,v,w);
    }
    int s2 = 0;
    gwm.dijkstraMatrix(s2);
    gwl.dijkstraList(s2);

    // 示例 3：含负权边（Bellman-Ford）
    cout << "\n=== 示例 C：含负权边（Bellman-Ford） ===\n";
    int n3 = 5;
    GraphList gneg(n3, true); // 有向图示例
    // 构造一个有向图，其中包含负权边但无负环
    gneg.addEdgeWeighted(0,1,6);
    gneg.addEdgeWeighted(0,2,7);
    gneg.addEdgeWeighted(1,2,8);
    gneg.addEdgeWeighted(1,3,5);
    gneg.addEdgeWeighted(1,4,-4);
    gneg.addEdgeWeighted(2,3,-3);
    gneg.addEdgeWeighted(2,4,9);
    gneg.addEdgeWeighted(3,1,-2);
    gneg.addEdgeWeighted(4,3,7);
    auto [hasNegCycle, dists] = gneg.bellmanFord(0);
    if (hasNegCycle) cout << "存在负权回路，最短路不存在。\n";

    cout << "\n示例结束。若需将程序改为从 stdin 读取图或交互式选择模式，请告知。\n";
    return 0;
}


