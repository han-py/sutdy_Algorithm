#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<int> bfs(const vector<vector<int>>& g, int s) {
    vector<int> ans, vis(g.size(), 0);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans.push_back(u);
        for (int v : g[u]) if (!vis[v]) { vis[v] = 1; q.push(v); }
    }
    return ans;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    vector<vector<int>> g = {{1, 2}, {3}, {3}, {}};
    auto ans = bfs(g, 0);
    cout << "BFS count = " << ans.size() << '\n';
    assert(!ans.empty());
    return 0;
}
