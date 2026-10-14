#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
vector<int> dijkstra(const vector<vector<pair<int,int>>>& g, int s) {
    const int INF = 1e9;
    vector<int> dist(g.size(), INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
    return dist;
}
vector<int> bellman_ford(int n, vector<tuple<int,int,int>> edges, int s) {
    const int INF = 1e9;
    vector<int> dist(n, INF);
    dist[s] = 0;
    for (int i = 1; i < n; ++i) {
        bool updated = false;
        for (auto [u, v, w] : edges) if (dist[u] < INF && dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            updated = true;
        }
        if (!updated) break;
    }
    return dist;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    vector<vector<pair<int,int>>> g(3);
    g[0] = {{1, 2}, {2, 5}};
    g[1] = {{2, 1}};
    auto d = dijkstra(g, 0);
    auto b = bellman_ford(3, {{0,1,2},{0,2,5},{1,2,1}}, 0);
    cout << "Dijkstra to 2 = " << d[2] << '\n';
    cout << "Bellman to 2 = " << b[2] << '\n';
    assert(d[2] == 3);
    return 0;
}
