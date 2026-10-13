
#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
int binary_search_demo(const vector<int>& a, int x) {
    int l = 0, r = (int)a.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == x) return m;
        if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
long long kadane(const vector<int>& a) {
    long long best = a[0], cur = a[0];
    for (size_t i = 1; i < a.size(); ++i) {
        cur = max<long long>(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}
vector<int> dijkstra_like(const vector<vector<pair<int,int>>>& g, int s) {
    const int INF = 1e9;
    vector<int> dist(g.size(), INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    vector<int> sorted{1, 3, 5, 7, 9};
    cout << "???? 7: " << binary_search_demo(sorted, 7) << '\n';
    vector<int> nums{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Kadane ?????: " << kadane(nums) << '\n';
    vector<vector<pair<int,int>>> g(4);
    g[0] = {{1, 2}, {2, 5}};
    g[1] = {{2, 1}, {3, 4}};
    g[2] = {{3, 1}};
    auto dist = dijkstra_like(g, 0);
    cout << "Dijkstra ?????? 3: " << dist[3] << '\n';
    unordered_map<string, int> memo;
    auto fib = [&](auto&& self, int n) -> int {
        if (n <= 1) return n;
        if (memo.count(to_string(n))) return memo[to_string(n)];
        return memo[to_string(n)] = self(self, n - 1) + self(self, n - 2);
    };
    cout << "????? fib(10): " << fib(fib, 10) << '\n';
    assert(binary_search_demo(sorted, 1) == 0);
    assert(kadane(nums) == 6);
    return 0;
}
