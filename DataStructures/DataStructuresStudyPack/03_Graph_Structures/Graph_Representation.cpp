#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
struct Edge { int to, w; };
class Graph {
public:
    explicit Graph(int n, bool directed = false) : g_(n), directed_(directed) {}
    void add_edge(int u, int v, int w = 1) {
        g_[u].push_back({v, w});
        if (!directed_) g_[v].push_back({u, w});
    }
    const vector<vector<Edge>>& adj() const { return g_; }
private:
    vector<vector<Edge>> g_;
    bool directed_;
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    Graph g(3, true);
    g.add_edge(0, 1, 2);
    g.add_edge(1, 2, 3);
    cout << "Adj size = " << g.adj().size() << '\n';
    assert(g.adj()[0].size() == 1);
    return 0;
}
