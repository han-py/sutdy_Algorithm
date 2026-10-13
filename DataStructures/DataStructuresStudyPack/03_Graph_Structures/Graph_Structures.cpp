
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;
struct Edge {
    int to;
    int w;
};
class Graph {
public:
    explicit Graph(int n, bool directed = false) : n_(n), directed_(directed), adj_(n) {}
    void add_edge(int u, int v, int w = 1) {
        adj_[u].push_back({v, w});
        if (!directed_) adj_[v].push_back({u, w});
    }
    const vector<vector<Edge>>& adj() const { return adj_; }
    int n() const { return n_; }
private:
    int n_;
    bool directed_;
    vector<vector<Edge>> adj_;
};
vector<int> dfs_order(const Graph& g, int start) {
    vector<int> order;
    vector<int> vis(g.n(), 0);
    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        order.push_back(u);
        for (auto [v, w] : g.adj()[u]) if (!vis[v]) dfs(v);
    };
    dfs(start);
    return order;
}
vector<int> bfs_order(const Graph& g, int start) {
    vector<int> order, vis(g.n(), 0);
    queue<int> q;
    q.push(start);
    vis[start] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (auto [v, w] : g.adj()[u]) if (!vis[v]) {
            vis[v] = 1;
            q.push(v);
        }
    }
    return order;
}
vector<int> topo_kahn(const Graph& g) {
    vector<int> indeg(g.n(), 0), order;
    for (int u = 0; u < g.n(); ++u) for (auto [v, w] : g.adj()[u]) ++indeg[v];
    queue<int> q;
    for (int i = 0; i < g.n(); ++i) if (!indeg[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (auto [v, w] : g.adj()[u]) if (--indeg[v] == 0) q.push(v);
    }
    return order;
}
vector<int> dijkstra(const Graph& g, int s) {
    const int INF = 1e9;
    vector<int> dist(g.n(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g.adj()[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
int kruskal_mst(int n, vector<tuple<int, int, int>> edges) {
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) { return get<2>(a) < get<2>(b); });
    vector<int> parent(n), sz(n, 1);
    iota(parent.begin(), parent.end(), 0);
    auto find = [&](auto&& self, int x) -> int {
        return parent[x] == x ? x : parent[x] = self(self, parent[x]);
    };
    int cost = 0;
    for (auto [u, v, w] : edges) {
        int fu = find(find, u), fv = find(find, v);
        if (fu == fv) continue;
        if (sz[fu] < sz[fv]) swap(fu, fv);
        parent[fv] = fu;
        sz[fu] += sz[fv];
        cost += w;
    }
    return cost;
}
vector<vector<int>> floyd(vector<vector<int>> dist) {
    int n = dist.size();
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] < 1e9 && dist[k][j] < 1e9)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    Graph g(6, true);
    g.add_edge(0, 1, 2);
    g.add_edge(0, 2, 5);
    g.add_edge(1, 3, 4);
    g.add_edge(2, 3, 1);
    g.add_edge(3, 4, 3);
    g.add_edge(4, 5, 1);
    auto dfs = dfs_order(g, 0);
    auto bfs = bfs_order(g, 0);
    auto topo = topo_kahn(g);
    auto dist = dijkstra(g, 0);
    cout << "DFS: "; for (int x : dfs) cout << x << ' '; cout << '\n';
    cout << "BFS: "; for (int x : bfs) cout << x << ' '; cout << '\n';
    cout << "???: "; for (int x : topo) cout << x << ' '; cout << '\n';
    cout << "Dijkstra ? 5 ???: " << dist[5] << '\n';
    vector<tuple<int, int, int>> edges = {{0,1,1},{0,2,2},{1,2,2},{1,3,3},{2,3,1}};
    cout << "Kruskal MST ??: " << kruskal_mst(4, edges) << '\n';
    const int INF = 1e9;
    vector<vector<int>> mat = {
        {0, 3, INF},
        {INF, 0, 1},
        {2, INF, 0}
    };
    auto all = floyd(mat);
    cout << "Floyd 0->2: " << all[0][2] << '\n';
    assert(dist[5] == 10);
    assert(!topo.empty());
    return 0;
}
