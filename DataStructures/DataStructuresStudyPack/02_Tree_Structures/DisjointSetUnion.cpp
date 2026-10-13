#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
class DSU {
public:
    explicit DSU(int n) : fa_(n), sz_(n, 1) { iota(fa_.begin(), fa_.end(), 0); }
    int find(int x) { return fa_[x] == x ? x : fa_[x] = find(fa_[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz_[a] < sz_[b]) swap(a, b);
        fa_[b] = a;
        sz_[a] += sz_[b];
        return true;
    }
    int size(int x) { return sz_[find(x)]; }
private:
    vector<int> fa_, sz_;
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    DSU dsu(5);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    cout << "DSU connected = " << (dsu.find(1) == dsu.find(2)) << '\n';
    cout << "DSU size(1) = " << dsu.size(1) << '\n';
    assert(dsu.size(1) == 2);
    return 0;
}
