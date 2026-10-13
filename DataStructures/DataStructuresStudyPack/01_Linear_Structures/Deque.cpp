#include <cassert>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
vector<int> sliding_window_max(const vector<int>& a, int k) {
    vector<int> ans;
    deque<int> dq;
    for (int i = 0; i < (int)a.size(); ++i) {
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) ans.push_back(a[dq.front()]);
    }
    return ans;
}
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    deque<int> dq;
    dq.push_front(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.push_back(3);
    cout << "Deque front/back = " << dq.front() << '/' << dq.back() << '\n';
    auto ans = sliding_window_max({1, 3, 1, 2, 0, 5}, 3);
    cout << "Sliding window count = " << ans.size() << '\n';
    assert(!ans.empty());
    return 0;
}
