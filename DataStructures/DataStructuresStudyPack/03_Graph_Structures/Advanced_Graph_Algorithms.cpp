#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
vector<int> comp;
vector<int> dfn, low, in_st, st;
int timer = 0, comp_cnt = 0;
void tarjan_scc(const vector<vector<int>>& g, int u) {
    dfn[u] = low[u] = ++timer;
    st.push_back(u);
    in_st[u] = 1;
    for (int v : g[u]) {
        if (!dfn[v]) {
            tarjan_scc(g, v);
            low[u] = min(low[u], low[v]);
        } else if (in_st[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        while (true) {
            int x = st.back(); st.pop_back();
            in_st[x] = 0;
            comp[x] = comp_cnt;
            if (x == u) break;
        }
        ++comp_cnt;
    }
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    vector<vector<int>> g = {{1}, {2}, {0, 3}, {}};
    int n = g.size();
    comp.assign(n, -1); dfn.assign(n, 0); low.assign(n, 0); in_st.assign(n, 0);
    for (int i = 0; i < n; ++i) if (!dfn[i]) tarjan_scc(g, i);
    cout << "SCC count = " << comp_cnt << '\n';
    assert(comp_cnt >= 1);
    return 0;
}
