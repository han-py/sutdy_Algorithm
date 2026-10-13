#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> g;
vector<int> vis, order;
void dfs(int u) {
    vis[u] = 1;
    order.push_back(u);
    for (int v : g[u]) if (!vis[v]) dfs(v);
}
vector<int> iterative_dfs(int s) {
    vector<int> ans, st = {s}, seen(g.size(), 0);
    while (!st.empty()) {
        int u = st.back(); st.pop_back();
        if (seen[u]) continue;
        seen[u] = 1;
        ans.push_back(u);
        for (int i = (int)g[u].size() - 1; i >= 0; --i) st.push_back(g[u][i]);
    }
    return ans;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    g = {{1, 2}, {3}, {3}, {}};
    vis.assign(g.size(), 0);
    dfs(0);
    auto it = iterative_dfs(0);
    cout << "DFS count = " << order.size() << '\n';
    cout << "Iterative DFS count = " << it.size() << '\n';
    assert(!order.empty());
    return 0;
}
