#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
class FenwickTree {
public:
    explicit FenwickTree(int n) : bit_(n + 1, 0) {}
    void add(int idx, long long delta) { for (int i = idx + 1; i < (int)bit_.size(); i += i & -i) bit_[i] += delta; }
    long long sum_prefix(int idx) const { long long res = 0; for (int i = idx + 1; i > 0; i -= i & -i) res += bit_[i]; return res; }
    long long range_sum(int l, int r) const { return l > r ? 0 : sum_prefix(r) - (l ? sum_prefix(l - 1) : 0); }
private:
    vector<long long> bit_;
};
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    FenwickTree bit(5);
    for (int i = 0; i < 5; ++i) bit.add(i, i + 1);
    cout << "Fenwick sum = " << bit.range_sum(1, 3) << '\n';
    assert(bit.range_sum(0, 4) == 15);
    return 0;
}
