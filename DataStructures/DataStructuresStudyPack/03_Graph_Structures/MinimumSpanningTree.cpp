#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
struct DSU {
    vector<int> fa, sz;
    DSU(int n) : fa(n), sz(n, 1) { iota(fa.begin(), fa.end(), 0); }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        fa[b] = a; sz[a] += sz[b];
        return true;
    }
};
int kruskal(int n, vector<tuple<int,int,int>> edges) {
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) { return get<2>(a) < get<2>(b); });
    DSU dsu(n);
    int cost = 0;
    for (auto [u, v, w] : edges) if (dsu.unite(u, v)) cost += w;
    return cost;
}
int prim(const vector<vector<pair<int,int>>>& g) {
    vector<int> vis(g.size(), 0);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, 0});
    int cost = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        cost += w;
        for (auto [v, ww] : g[u]) if (!vis[v]) pq.push({ww, v});
    }
    return cost;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    vector<tuple<int,int,int>> edges = {{0,1,1},{0,2,2},{1,2,2},{1,3,3},{2,3,1}};
    cout << "Kruskal = " << kruskal(4, edges) << '\n';
    vector<vector<pair<int,int>>> g(4);
    g[0] = {{1,1},{2,2}};
    g[1] = {{0,1},{2,2},{3,3}};
    g[2] = {{0,2},{1,2},{3,1}};
    g[3] = {{1,3},{2,1}};
    cout << "Prim = " << prim(g) << '\n';
    assert(kruskal(4, edges) > 0);
    return 0;
}
