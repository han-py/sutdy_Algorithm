#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<int> kahn(const vector<vector<int>>& g) {
    vector<int> indeg(g.size(), 0), ans;
    for (size_t u = 0; u < g.size(); ++u) for (int v : g[u]) ++indeg[v];
    queue<int> q;
    for (int i = 0; i < (int)g.size(); ++i) if (!indeg[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    return ans;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    vector<vector<int>> g = {{1, 2}, {3}, {3}, {}};
    auto ans = kahn(g);
    cout << "Topo size = " << ans.size() << '\n';
    assert(ans.size() == 4);
    return 0;
}
