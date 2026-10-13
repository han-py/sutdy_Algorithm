#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
class SegmentTree {
public:
    explicit SegmentTree(vector<long long> a) : n_(a.size()), tree_(n_ * 4), lazy_(n_ * 4, 0) { build(1, 0, n_ - 1, a); }
    long long query(int l, int r) { return query(1, 0, n_ - 1, l, r); }
    void add(int l, int r, long long d) { add(1, 0, n_ - 1, l, r, d); }
private:
    int n_;
    vector<long long> tree_, lazy_;
    void build(int p, int l, int r, const vector<long long>& a) {
        if (l == r) { tree_[p] = a[l]; return; }
        int m = (l + r) / 2;
        build(p * 2, l, m, a);
        build(p * 2 + 1, m + 1, r, a);
        tree_[p] = tree_[p * 2] + tree_[p * 2 + 1];
    }
    void apply(int p, int l, int r, long long d) { tree_[p] += d * (r - l + 1); lazy_[p] += d; }
    void push(int p, int l, int r) { if (lazy_[p] && l != r) { int m = (l + r) / 2; apply(p * 2, l, m, lazy_[p]); apply(p * 2 + 1, m + 1, r, lazy_[p]); lazy_[p] = 0; } }
    void add(int p, int l, int r, int ql, int qr, long long d) {
        if (ql <= l && r <= qr) { apply(p, l, r, d); return; }
        push(p, l, r);
        int m = (l + r) / 2;
        if (ql <= m) add(p * 2, l, m, ql, qr, d);
        if (qr > m) add(p * 2 + 1, m + 1, r, ql, qr, d);
        tree_[p] = tree_[p * 2] + tree_[p * 2 + 1];
    }
    long long query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree_[p];
        push(p, l, r);
        int m = (l + r) / 2;
        long long ans = 0;
        if (ql <= m) ans += query(p * 2, l, m, ql, qr);
        if (qr > m) ans += query(p * 2 + 1, m + 1, r, ql, qr);
        return ans;
    }
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    SegmentTree seg({1, 2, 3, 4, 5});
    seg.add(1, 3, 2);
    cout << "SegmentTree query = " << seg.query(0, 4) << '\n';
    assert(seg.query(0, 4) == 21);
    return 0;
}
