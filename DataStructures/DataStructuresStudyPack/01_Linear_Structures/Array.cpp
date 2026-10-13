#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
class DynamicArray {
public:
    void push_back(int x) { a_.push_back(x); }
    void insert(int pos, int x) { a_.insert(a_.begin() + pos, x); }
    void erase(int pos) { a_.erase(a_.begin() + pos); }
    int find(int x) const {
        for (int i = 0; i < (int)a_.size(); ++i) if (a_[i] == x) return i;
        return -1;
    }
    const vector<int>& data() const { return a_; }
private:
    vector<int> a_;
};
vector<int> prefix_sum(const vector<int>& a) {
    vector<int> p(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); ++i) p[i + 1] = p[i] + a[i];
    return p;
}
vector<int> difference_array(const vector<int>& a) {
    vector<int> d(a.size(), 0);
    if (!a.empty()) d[0] = a[0];
    for (size_t i = 1; i < a.size(); ++i) d[i] = a[i] - a[i - 1];
    return d;
}
int range_sum(const vector<int>& prefix, int l, int r) {
    return prefix[r + 1] - prefix[l];
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    DynamicArray arr;
    for (int x : {1, 2, 3, 4}) arr.push_back(x);
    arr.insert(2, 99);
    arr.erase(0);
    cout << "Array size = " << arr.data().size() << '\n';
    cout << "Find 99 = " << arr.find(99) << '\n';
    auto p = prefix_sum(arr.data());
    cout << "Range sum [1, 3] = " << range_sum(p, 1, 3) << '\n';
    auto d = difference_array(arr.data());
    cout << "Difference size = " << d.size() << '\n';
    assert(arr.find(99) == 1);
    return 0;
}
